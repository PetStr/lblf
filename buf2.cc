#include <cstring>
#include <fstream>

using namespace std;

/*** vxor_streambuf class ******************************************/

class vxor_streambuf: public streambuf
{
public:
    vxor_streambuf(streambuf *buffer, const int width) :
        buffer(buffer),
        size(width / 2)
    {
        previous_line = new char[size];
        memset(previous_line, 0, size);
        current_line = new char[size];
        setg(0, 0, 0);
        setp(current_line, current_line + size);
    }

    virtual ~vxor_streambuf()
    {
        sync();
        delete[] previous_line;
        delete[] current_line;
    }

    virtual streambuf::int_type underflow()
    {
        // Read line from original buffer
        streamsize read = buffer->sgetn(current_line, size);
        if (!read) return traits_type::eof();

        // Do vertical XOR decoding
        for (int i = 0; i < size; i += 1)
            {
                current_line[i] ^= previous_line[i];
                previous_line[i] = current_line[i];
            }

        setg(current_line, current_line, current_line + read);
        return traits_type::to_int_type(*gptr());
    }

    virtual streambuf::int_type overflow(streambuf::int_type value)
    {
        int write = pptr() - pbase();
        if (write)
            {
                // Do vertical XOR encoding
                for (int i = 0; i < size; i += 1)
                    {
                        char tmp = current_line[i];
                        current_line[i] ^= previous_line[i];
                        previous_line[i] = tmp;
                    }

                // Write line to original buffer
                streamsize written = buffer->sputn(current_line, write);
                if (written != write) return traits_type::eof();
            }

        setp(current_line, current_line + size);
        if (!traits_type::eq_int_type(value, traits_type::eof())) sputc(value);
        return traits_type::not_eof(value);
    };

    virtual int sync()
    {
        streambuf::int_type result = this->overflow(traits_type::eof());
        buffer->pubsync();
        return traits_type::eq_int_type(result, traits_type::eof()) ? -1 : 0;
    }

private:
    streambuf *buffer;
    int size;
    char *previous_line;
    char *current_line;
};


/*** vxor_istream class ********************************************/

class vxor_istream: public istream
{
public:
    vxor_istream(istream &stream, const int width) :
        istream(new vxor_streambuf(stream.rdbuf(), width)) {}

    virtual ~vxor_istream()
    {
        delete rdbuf();
    }
};


/*** vxor_ostream class ********************************************/

class vxor_ostream: public ostream
{
public:
    vxor_ostream(ostream &stream, const int width) :
        ostream(new vxor_streambuf(stream.rdbuf(), width)) {}

    virtual ~vxor_ostream()
    {
        delete rdbuf();
    }
};


/*** Test main method **********************************************/

int main()
{
    // Read data
    ifstream infile("test.img");
    vxor_istream in(infile, 288);
    char data[144 * 128];
    in.read(data, 144 * 128);
    infile.close();

    // Write data
    ofstream outfile("test2.img");
    vxor_ostream out(outfile, 288);
    out.write(data, 144 * 128);
    out.flush();
    outfile.close();

    return 0;
}
