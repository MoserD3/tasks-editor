#pragma once

#pragma pack(push, 1)
class VAL3
{
private:
    unsigned char data[3];

public:
    VAL3(unsigned int v = 0) { set_val(v); };

    void set_val(unsigned int v)
    {
        unsigned char *c = reinterpret_cast<unsigned char*>(&v);
        data[0] = c[0];
        data[1] = c[1];
        data[2] = c[2];
    };

    unsigned int get_val()
    {
        unsigned int v = 0;
        unsigned char *c = reinterpret_cast<unsigned char*>(&v);
        c[0] = data[0];
        c[1] = data[1];
        c[2] = data[2];
        return v;
    };
};
#pragma pack(pop)
