#ifndef COUNT_ID_H_
#define COUNT_ID_H_


struct dbc_names
{
    const char * const short_name;
    const char * const file_name;
};


static const dbc_names DBC[] =
{
    {"AdvLightSubnet_postfix.dbc","AdvLightSubnet_postfix.dbc"},
    {"Backbone1J1939_postfix.dbc","Backbone1J1939_postfix.dbc"},
    {"Backbone2_postfix.dbc","Backbone2_postfix.dbc"},
    {"BBProprietaryNet_postfix.dbc","BBProprietaryNet_postfix.dbc"},
    {"CabSubnet_postfix.dbc","CabSubnet_postfix.dbc"},
    {"ChassisSubnet_postfix.dbc","ChassisSubnet_postfix.dbc"},
    {"DiagnosticsLink_postfix.dbc","DiagnosticsLink_postfix.dbc"},
    {"DisplaySubnet_postfix.dbc","DisplaySubnet_postfix.dbc"},
    {"FMSNet_postfix.dbc","FMSNet_postfix.dbc"},
    {"InfotainmentSubnet_postfix.dbc","InfotainmentSubnet_postfix.dbc"},
    {"SafetySensorSubnet1_postfix.dbc","SafetySensorSubnet1_postfix.dbc"},
    {"SafetySubnet1_postfix.dbc","SafetySubnet1_postfix.dbc"},
    {"SafetySubnet2_0_postfix.dbc","SafetySubnet2_0_postfix.dbc"},
    {"SafetySubnet2_1_postfix.dbc","SafetySubnet2_1_postfix.dbc"},
    {"SecuritySubnet_postfix.dbc","SecuritySubnet_postfix.dbc"},
    {"engine_subnet.dbc","engine_subnet.dbc"},
    {"engine_subnet_t2.dbc","engine_subnet_t2.dbc"},
    {"ptcan.dbc","ptcan.dbc"},
    {"ptcan_t2.dbc","ptcan_t2.dbc"}
};

const int DBC_number = 19;

#endif