#include "../include/colorlut.hpp"

ColorLut::ColorLut()
{
    LUT[0x000000] = 0;
    LUT[0x800000] = 1;
    LUT[0x008000] = 2;
    LUT[0x808000] = 3;
    LUT[0x000080] = 4;
    LUT[0x800080] = 5;
    LUT[0x008080] = 6;
    LUT[0xc0c0c0] = 7;
    LUT[0x808080] = 8;
    LUT[0xff0000] = 9;
    LUT[0x00ff00] = 10;
    LUT[0xffff00] = 11;
    LUT[0x0000ff] = 12;
    LUT[0xff00ff] = 13;
    LUT[0x00ffff] = 14;
    LUT[0xffffff] = 15;
    LUT[0x000000] = 16;
    LUT[0x00005f] = 17;
    LUT[0x000087] = 18;
    LUT[0x0000af] = 19;
    LUT[0x0000d7] = 20;
    LUT[0x0000ff] = 21;
    LUT[0x005f00] = 22;
    LUT[0x005f5f] = 23;
    LUT[0x005f87] = 24;
    LUT[0x005faf] = 25;
    LUT[0x005fd7] = 26;
    LUT[0x005fff] = 27;
    LUT[0x008700] = 28;
    LUT[0x00875f] = 29;
    LUT[0x008787] = 30;
    LUT[0x0087af] = 31;
    LUT[0x0087d7] = 32;
    LUT[0x0087ff] = 33;
    LUT[0x00af00] = 34;
    LUT[0x00af5f] = 35;
    LUT[0x00af87] = 36;
    LUT[0x00afaf] = 37;
    LUT[0x00afd7] = 38;
    LUT[0x00afff] = 39;
    LUT[0x00d700] = 40;
    LUT[0x00d75f] = 41;
    LUT[0x00d787] = 42;
    LUT[0x00d7af] = 43;
    LUT[0x00d7d7] = 44;
    LUT[0x00d7ff] = 45;
    LUT[0x00ff00] = 46;
    LUT[0x00ff5f] = 47;
    LUT[0x00ff87] = 48;
    LUT[0x00ffaf] = 49;
    LUT[0x00ffd7] = 50;
    LUT[0x00ffff] = 51;
    LUT[0x5f0000] = 52;
    LUT[0x5f005f] = 53;
    LUT[0x5f0087] = 54;
    LUT[0x5f00af] = 55;
    LUT[0x5f00d7] = 56;
    LUT[0x5f00ff] = 57;
    LUT[0x5f5f00] = 58;
    LUT[0x5f5f5f] = 59;
    LUT[0x5f5f87] = 60;
    LUT[0x5f5faf] = 61;
    LUT[0x5f5fd7] = 62;
    LUT[0x5f5fff] = 63;
    LUT[0x5f8700] = 64;
    LUT[0x5f875f] = 65;
    LUT[0x5f8787] = 66;
    LUT[0x5f87af] = 67;
    LUT[0x5f87af] = 68;
    LUT[0x5f87ff] = 69;
    LUT[0x5faf00] = 70;
    LUT[0x5faf5f] = 71;
    LUT[0x5faf87] = 72;
    LUT[0x5fafaf] = 73;
    LUT[0x5fafd7] = 74;
    LUT[0x5fafff] = 75;
    LUT[0x5fd700] = 76;
    LUT[0x5fd75f] = 77;
    LUT[0x5fd787] = 78;
    LUT[0x5fd7af] = 79;
    LUT[0x5fd7d7] = 80;
    LUT[0x5fd7ff] = 81;
    LUT[0x5fff00] = 82;
    LUT[0x5fff5f] = 83;
    LUT[0x5fff87] = 84;
    LUT[0x5fffaf] = 85;
    LUT[0x5fffd7] = 86;
    LUT[0x5fffff] = 87;
    LUT[0x870000] = 88;
    LUT[0x87005f] = 89;
    LUT[0x870087] = 90;
    LUT[0x8700af] = 91;
    LUT[0x8700d7] = 92;
    LUT[0x8700ff] = 93;
    LUT[0x875f00] = 94;
    LUT[0x875f5f] = 95;
    LUT[0x875f87] = 96;
    LUT[0x875faf] = 97;
    LUT[0x875fd7] = 98;
    LUT[0x875fff] = 99;
    LUT[0x878700] = 100;
    LUT[0x87875f] = 101;
    LUT[0x878787] = 102;
    LUT[0x8787af] = 103;
    LUT[0x8787d7] = 104;
    LUT[0x8787ff] = 105;
    LUT[0x87af00] = 106;
    LUT[0x87af5f] = 107;
    LUT[0x87af87] = 108;
    LUT[0x87afaf] = 109;
    LUT[0x87afd7] = 110;
    LUT[0x87afff] = 111;
    LUT[0x87d700] = 112;
    LUT[0x87d75f] = 113;
    LUT[0x87d787] = 114;
    LUT[0x87d7af] = 115;
    LUT[0x87d7d7] = 116;
    LUT[0x87d7ff] = 117;
    LUT[0x87ff00] = 118;
    LUT[0x87ff5f] = 119;
    LUT[0x87ff87] = 120;
    LUT[0x87ffaf] = 121;
    LUT[0x87ffd7] = 122;
    LUT[0x87ffff] = 123;
    LUT[0xaf0000] = 124;
    LUT[0xaf005f] = 125;
    LUT[0xaf0087] = 126;
    LUT[0xaf00af] = 127;
    LUT[0xaf00d7] = 128;
    LUT[0xaf00ff] = 129;
    LUT[0xaf5f00] = 130;
    LUT[0xaf5f5f] = 131;
    LUT[0xaf5f87] = 132;
    LUT[0xaf5faf] = 133;
    LUT[0xaf5fd7] = 134;
    LUT[0xaf5fff] = 135;
    LUT[0xaf8700] = 136;
    LUT[0xaf875f] = 137;
    LUT[0xaf8787] = 138;
    LUT[0xaf87af] = 139;
    LUT[0xaf87d7] = 140;
    LUT[0xaf87ff] = 141;
    LUT[0xafaf00] = 142;
    LUT[0xafaf5f] = 143;
    LUT[0xafaf87] = 144;
    LUT[0xafafaf] = 145;
    LUT[0xafafd7] = 146;
    LUT[0xafafff] = 147;
    LUT[0xafd700] = 148;
    LUT[0xafd75f] = 149;
    LUT[0xafd787] = 150;
    LUT[0xafd7af] = 151;
    LUT[0xafd7d7] = 152;
    LUT[0xafd7ff] = 153;
    LUT[0xafff00] = 154;
    LUT[0xafff5f] = 155;
    LUT[0xafff87] = 156;
    LUT[0xafffaf] = 157;
    LUT[0xafffd7] = 158;
    LUT[0xafffff] = 159;
    LUT[0xd70000] = 160;
    LUT[0xd7005f] = 161;
    LUT[0xd70087] = 162;
    LUT[0xd700af] = 163;
    LUT[0xd700d7] = 164;
    LUT[0xd700ff] = 165;
    LUT[0xd75f00] = 166;
    LUT[0xd75f5f] = 167;
    LUT[0xd75f87] = 168;
    LUT[0xd75faf] = 169;
    LUT[0xd75fd7] = 170;
    LUT[0xd75fff] = 171;
    LUT[0xd78700] = 172;
    LUT[0xd7875f] = 173;
    LUT[0xd78787] = 174;
    LUT[0xd787af] = 175;
    LUT[0xd787d7] = 176;
    LUT[0xd787ff] = 177;
    LUT[0xd7af00] = 178;
    LUT[0xd7af5f] = 179;
    LUT[0xd7af87] = 180;
    LUT[0xd7afaf] = 181;
    LUT[0xd7afd7] = 182;
    LUT[0xd7afff] = 183;
    LUT[0xd7d700] = 184;
    LUT[0xd7d75f] = 185;
    LUT[0xd7d787] = 186;
    LUT[0xd7d7af] = 187;
    LUT[0xd7d7d7] = 188;
    LUT[0xd7d7ff] = 189;
    LUT[0xd7ff00] = 190;
    LUT[0xd7ff5f] = 191;
    LUT[0xd7ff87] = 192;
    LUT[0xd7ffaf] = 193;
    LUT[0xd7ffd7] = 194;
    LUT[0xd7ffff] = 195;
    LUT[0xff0000] = 196;
    LUT[0xff005f] = 197;
    LUT[0xff0087] = 198;
    LUT[0xff00af] = 199;
    LUT[0xff00d7] = 200;
    LUT[0xff00ff] = 201;
    LUT[0xff5f00] = 202;
    LUT[0xff5f5f] = 203;
    LUT[0xff5f87] = 204;
    LUT[0xff5faf] = 205;
    LUT[0xff5fd7] = 206;
    LUT[0xff5fff] = 207;
    LUT[0xff8700] = 208;
    LUT[0xff875f] = 209;
    LUT[0xff8787] = 210;
    LUT[0xff87af] = 211;
    LUT[0xff87d7] = 212;
    LUT[0xff87ff] = 213;
    LUT[0xffaf00] = 214;
    LUT[0xffaf5f] = 215;
    LUT[0xffaf87] = 216;
    LUT[0xffafaf] = 217;
    LUT[0xffafd7] = 218;
    LUT[0xffafff] = 219;
    LUT[0xffd700] = 220;
    LUT[0xffd75f] = 221;
    LUT[0xffd787] = 222;
    LUT[0xffd7af] = 223;
    LUT[0xffd7d7] = 224;
    LUT[0xffd7ff] = 225;
    LUT[0xffff00] = 226;
    LUT[0xffff5f] = 227;
    LUT[0xffff87] = 228;
    LUT[0xffffaf] = 229;
    LUT[0xffffd7] = 230;
    LUT[0xffffff] = 231;
    LUT[0x080808] = 232;
    LUT[0x121212] = 233;
    LUT[0x1c1c1c] = 234;
    LUT[0x262626] = 235;
    LUT[0x303030] = 236;
    LUT[0x3a3a3a] = 237;
    LUT[0x444444] = 238;
    LUT[0x4e4e4e] = 239;
    LUT[0x585858] = 240;
    LUT[0x626262] = 241;
    LUT[0x6c6c6c] = 242;
    LUT[0x767676] = 243;
    LUT[0x808080] = 244;
    LUT[0x8a8a8a] = 245;
    LUT[0x949494] = 246;
    LUT[0x9e9e9e] = 247;
    LUT[0xa8a8a8] = 248;
    LUT[0xb2b2b2] = 249;
    LUT[0xbcbcbc] = 250;
    LUT[0xc6c6c6] = 251;
    LUT[0xd0d0d0] = 252;
    LUT[0xdadada] = 253;
    LUT[0xe4e4e4] = 254;
    LUT[0xeeeeee] = 255;
}

int ColorLut::rgb_to_8bit(double r, double g, double b)
{

    int ri = static_cast<int>(r), gi = static_cast<int>(g), bi = static_cast<int>(b);

    if (ri < 47)
    {
        ri = 0;
    }
    else if (ri < 115)
    {
        ri = 95;
    }
    else if (ri < 155)
    {
        ri = 135;
    }
    else if (ri < 195)
    {
        ri = 175;
    }
    else if (ri < 235)
    {
        ri = 215;
    }
    else
    {
        ri = 255;
    }

    if (gi < 47)
    {
        gi = 0;
    }
    else if (gi < 115)
    {
        gi = 95;
    }
    else if (gi < 155)
    {
        gi = 135;
    }
    else if (gi < 195)
    {
        gi = 175;
    }
    else if (gi < 235)
    {
        gi = 215;
    }
    else
    {
        gi = 255;
    }

    if (bi < 47)
    {
        bi = 0;
    }
    else if (bi < 115)
    {
        bi = 95;
    }
    else if (bi < 155)
    {
        bi = 135;
    }
    else if (bi < 195)
    {
        bi = 175;
    }
    else if (bi < 235)
    {
        bi = 215;
    }
    else
    {
        bi = 255;
    }
    int hex = ((ri << 16) & 0xff0000) | ((gi << 8) & 0x00ff00) | (bi & 0x0000ff);
    return LUT[hex];
}
