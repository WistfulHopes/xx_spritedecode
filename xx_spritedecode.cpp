#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <algorithm>
#include <vector>
#include "Windows.h"
#include "lodepng.h"

#define HIBYTE(num) (num & 0xFF000000 >> 24) & 0xFF
#define HIDWORD(num) (num & 0xFFFFFFFF00000000 >> 32) & 0xFFFFFFFF
#define LODWORD(num) (num & 0xFFFFFFFF)
#define __PAIR64__(num1, num2) num1 << 32 + num2
#define BYTEn(x, n)   (*((char*)&(x)+n))
#define BYTE1(x)   BYTEn(x,  1)
#define LOW_IND(x,part_type)   0
#define LOBYTE(x)  BYTEn(x,LOW_IND(x,_BYTE))

void SetLowDWORD(uint64_t* out, uint32_t val)
{
  *out = __PAIR64__(HIDWORD(*out), val);
}

void SetHighDWORD(uint64_t* out, uint32_t val)
{
  *out = __PAIR64__(val, LODWORD(*out));
}

char* decode_basic(uint16_t* CompressedSpriteData, char* dest) {  
  int v3; // esi
  unsigned int result; // eax
  uint16_t *v5; // ebx
  int v6; // ecx
  size_t v7; // esi
  char v8; // [esp+Ch] [ebp-8h]
  int v9; // [esp+10h] [ebp-4h]
  char *v10; // [esp+1Ch] [ebp+8h]

  v3 = CompressedSpriteData[1] | (*CompressedSpriteData << 16);
  result = 0;
  v5 = CompressedSpriteData + 2;
  v10 = dest;
  v9 = v3;
  if ( v3 > 0 )
  {
  while ( 1 )
  {
    v6 = ((char)result - 1) & 0xF;
    result = (v5[1] | (*v5 << 16)) >> v6;
    v8 = v6;
    v5 = &v5[-(v6 != 0) + 2];
    if ( (result & 0x10000) != 0 )
    {
    *dest = BYTE1(result);
    dest[1] = result;
    dest += 2;
    }
    else
    {
    v7 = (result & 0x7F) + 3;
    result = (unsigned int)memcpy(dest, &v10[(uint16_t)result >> 7], v7);
    dest += v7;
    v3 = v9;
    }
    if ( dest - v10 > 512 )
    {
    result = (unsigned int)(dest - 512);
    v10 = dest - 512;
    }
    v9 = --v3;
    if ( v3 <= 0 )
    break;
    LOBYTE(result) = v8;
  }
  }
  return dest;
}

void decode(const char *name)
{
  std::ifstream in(name, std::ios::binary);
  if (!in)
  {
    std::cerr << "Couldn't open " << name << std::endl;
    return;
  }

  std::vector<char> data = std::vector<char>(std::istreambuf_iterator<char>(in),
  (std::istreambuf_iterator<char>()));

  uint16_t* CompressedSpriteData;
  if (((uint16_t*)data.data())[1] == 0)
  {
      CompressedSpriteData = (uint16_t*)&data.data()[16];
  }
  else
  {
      if (((uint16_t*)data.data())[2] == 8)
      {
          CompressedSpriteData = (uint16_t*)&data.data()[1040];
      }
      else 
      {
          CompressedSpriteData = (uint16_t*)&data.data()[80];
      }
  }

  size_t arraySize = data.size();
  char* dest = (char*)calloc(1, 0x3800000);
  char* origPos = dest;

  if ((uint16_t)data.data()[0] & 4)
  {
  uint32_t uVar1;
  uint32_t uVar2;
  int iVar3;
  uint32_t uVar4;
  uint32_t uVar5;
  uint32_t uVar6;
  uint32_t uVar7;
  uint32_t uVar8;
  uint32_t uVar9;
  uint32_t *local_90;
  int local_8c;
  uint32_t *local_88;
  uint32_t local_84;
  uint32_t local_80;
  uint32_t local_7c;
  uint32_t local_74;
  uint32_t local_6c;
  uint32_t local_68;
  uint32_t *local_64;
  uint32_t local_60;
  uint32_t local_5c;
  int local_58;
  int local_54;
  int local_48;
  uint32_t local_44;
  uint32_t local_40;
  uint32_t local_3c;
  uint32_t local_38;
  uint32_t local_24;
  int local_20;
  uint32_t local_1c;
  uint32_t local_18;
  uint32_t *local_14;
  
  uVar8 = (uint32_t)*CompressedSpriteData;
  local_90 = (uint32_t *)(CompressedSpriteData + (uint32_t)CompressedSpriteData[4] * 4);
  local_24 = (uint32_t)CompressedSpriteData[1];
  iVar3 = 0;
  local_88 = (uint32_t *)(CompressedSpriteData + (uint32_t)CompressedSpriteData[5] * 4);
  uVar9 = 0;
  local_64 = (uint32_t *)(CompressedSpriteData + (uint32_t)CompressedSpriteData[6] * 4);
  local_58 = 0;
  local_14 = (uint32_t *)(CompressedSpriteData + (uint32_t)CompressedSpriteData[7] * 4);
  uVar1 = 0;
  local_84 = 0;
  local_80 = 0;
  local_8c = 0;
  local_60 = 0;
  local_5c = 0;
  local_54 = 0;
  local_44 = 0;
  local_40 = 0;
  local_1c = 0;
  local_18 = 0;
  local_20 = 0;
  local_48 = 0;
  local_7c = 0;
  local_74 = 0;
  local_6c = 0;
  local_68 = 0;
  local_3c = 0;
  local_38 = 0;
  uVar4 = (int)uVar8 >> 1;
  if ((CompressedSpriteData[3] == 5) &&
    (local_24 = (int)local_24 >> 1, uVar2 = local_1c, uVar6 = uVar4, local_24 != 0)) {
    do {
    while (uVar6 = uVar6 - 1, local_1c = uVar2, -1 < (int)uVar6) {
      if (local_48 == 0) {
      if (local_8c == 0) {
        local_8c = 0x40;
        local_84 = *local_90;
        local_80 = local_90[1];
        local_90 = local_90 + 2;
      }
      uVar7 = local_84 >> 1 | local_80 << 0x1f;
      local_80 = local_80 >> 1;
      local_8c = local_8c + -1;
      if ((local_84 & 1) == 0) {
        if (local_8c == 0) {
        local_8c = 0x40;
        uVar7 = *local_90;
        local_80 = local_90[1];
        local_90 = local_90 + 2;
        }
        uVar1 = uVar7 >> 1 | local_80 << 0x1f;
        local_80 = local_80 >> 1;
        local_8c = local_8c + -1;
        if ((uVar7 & 1) == 0) {
        if (local_8c == 0) {
          uVar1 = *local_90;
          local_80 = local_90[1];
          local_90 = local_90 + 2;
          local_8c = 0x40;
        }
        uVar9 = uVar1 >> 1 | local_80 << 0x1f;
        local_80 = local_80 >> 1;
        local_8c = local_8c + -1;
        if ((uVar1 & 1) != 0) {
          if (iVar3 == 0) {
          iVar3 = 0xc;
          local_44 = *local_64;
          local_40 = local_64[1];
          local_64 = local_64 + 2;
          }
          uVar1 = local_40 << 0x1b;
          local_40 = local_40 >> 5;
          local_74 = local_44 & 0x1f;
          iVar3 = iVar3 + -1;
          local_58 = iVar3;
          local_44 = local_44 >> 5 | uVar1;
        }
        if (local_8c == 0) {
          uVar9 = *local_90;
          local_80 = local_90[1];
          local_90 = local_90 + 2;
          local_8c = 0x40;
        }
        local_84 = uVar9 >> 1 | local_80 << 0x1f;
        local_80 = local_80 >> 1;
        local_8c = local_8c + -1;
        if ((uVar9 & 1) != 0) {
          if (iVar3 == 0) {
          iVar3 = 0xc;
          local_44 = *local_64;
          local_40 = local_64[1];
          local_64 = local_64 + 2;
          }
          uVar1 = local_40 << 0x1b;
          local_7c = local_44 & 0x1f;
          local_40 = local_40 >> 5;
          iVar3 = iVar3 + -1;
          local_58 = iVar3;
          local_44 = local_44 >> 5 | uVar1;
        }
        if (local_54 == 0) {
          local_54 = 0x10;
          local_60 = *local_88;
          local_5c = local_88[1];
          local_88 = local_88 + 2;
        }
        uVar2 = local_5c << 0x1c;
        local_5c = local_5c >> 4;
        local_54 = local_54 + -1;
        uVar1 = local_74;
        if ((local_60 & 4) != 0) {
          uVar1 = local_7c;
        }
        uVar9 = local_74;
        if ((local_60 & 8) != 0) {
          uVar9 = local_7c;
        }
        uVar9 = (uVar1 << 8 | uVar9) << 0x10;
        uVar1 = local_74;
        if ((local_60 & 1) != 0) {
          uVar1 = local_7c;
        }
        uVar7 = local_74;
        if ((local_60 & 2) != 0) {
          uVar7 = local_7c;
        }
        uVar1 = (uVar1 << 8 | uVar7) << 0x10;
        local_60 = local_60 >> 4 | uVar2;
        }
        else {
        if (local_8c == 0) {
          uVar1 = *local_90;
          local_80 = local_90[1];
          local_90 = local_90 + 2;
          local_8c = 0x40;
        }
        uVar2 = uVar1 >> 1 | local_80 << 0x1f;
        local_80 = local_80 >> 1;
        local_8c = local_8c + -1;
        if ((uVar1 & 1) == 0) {
          if (local_8c == 0) {
          uVar2 = *local_90;
          local_80 = local_90[1];
          local_90 = local_90 + 2;
          local_8c = 0x40;
          }
          local_84 = uVar2 >> 1 | local_80 << 0x1f;
          local_80 = local_80 >> 1;
          local_8c = local_8c + -1;
          if ((uVar2 & 1) == 0) {
          uVar1 = (local_74 | local_74 << 8) << 0x10;
          uVar9 = uVar1;
          }
          else {
          uVar1 = (local_7c | local_7c << 8) << 0x10;
          uVar9 = uVar1;
          }
        }
        else {
          if (iVar3 == 0) {
          iVar3 = 0xc;
          local_44 = *local_64;
          local_40 = local_64[1];
          local_64 = local_64 + 2;
          }
          uVar7 = local_40 << 0x1b;
          local_74 = local_44 & 0x1f;
          local_40 = local_40 >> 5;
          local_58 = iVar3 + -1;
          uVar1 = (local_74 | local_74 << 8) << 0x10;
          iVar3 = local_58;
          uVar9 = uVar1;
          local_84 = uVar2;
          local_44 = local_44 >> 5 | uVar7;
        }
        }
      }
      else {
        if (local_8c == 0) {
        local_8c = 0x40;
        uVar7 = *local_90;
        local_80 = local_90[1];
        local_90 = local_90 + 2;
        }
        uVar5 = uVar7 >> 1 | local_80 << 0x1f;
        local_80 = local_80 >> 1;
        local_8c = local_8c + -1;
        if ((uVar7 & 1) == 0) {
        if (local_8c == 0) {
          uVar5 = *local_90;
          local_80 = local_90[1];
          local_90 = local_90 + 2;
          local_8c = 0x40;
        }
        local_84 = uVar5 >> 1 | local_80 << 0x1f;
        local_80 = local_80 >> 1;
        local_8c = local_8c + -1;
        iVar3 = local_58;
        if ((uVar5 & 1) != 0) {
          if (local_20 == 0) {
          uVar2 = *local_14;
          local_18 = local_14[1];
          local_14 = local_14 + 2;
          local_20 = 8;
          }
          local_1c = uVar2 >> 8 | local_18 << 0x18;
          local_18 = local_18 >> 8;
          local_20 = local_20 + -1;
          local_48 = (uVar2 & 0xff) + 3;
        }
        }
        else {
        if (local_58 == 0) {
          local_44 = *local_64;
          local_40 = local_64[1];
          local_64 = local_64 + 2;
          local_58 = 0xc;
        }
        uVar1 = local_44 >> 5 | local_40 << 0x1b;
        local_40 = local_40 >> 5;
        local_58 = local_58 + -1;
        if (local_58 == 0) {
          uVar1 = *local_64;
          local_40 = local_64[1];
          local_64 = local_64 + 2;
          local_58 = 0xc;
        }
        local_74 = uVar1 & 0x1f;
        uVar1 = uVar1 >> 5 | local_40 << 0x1b;
        local_40 = local_40 >> 5;
        local_58 = local_58 + -1;
        if (local_58 == 0) {
          uVar1 = *local_64;
          local_40 = local_64[1];
          local_64 = local_64 + 2;
          local_58 = 0xc;
        }
        uVar2 = uVar1 >> 5 | local_40 << 0x1b;
        uVar7 = local_40 >> 5;
        local_58 = local_58 + -1;
        if (local_58 == 0) {
          uVar2 = *local_64;
          uVar7 = local_64[1];
          local_64 = local_64 + 2;
          local_58 = 0xc;
        }
        local_7c = uVar2 & 0x1f;
        local_40 = uVar7 >> 5;
        uVar1 = (uVar1 & 0x1f) << 0x10 | local_7c << 0x18;
        local_58 = local_58 + -1;
        iVar3 = local_58;
        uVar9 = (local_44 & 0x1f) << 0x10 | local_74 << 0x18;
        local_84 = uVar5;
        local_44 = uVar2 >> 5 | uVar7 << 0x1b;
        }
      }
      }
      else {
      local_48 = local_48 + -1;
      }
      uVar2 = local_1c;
      if ((uVar6 & 3) == 0) {
      *(uint32_t *)((int)dest + 4) = local_38 | uVar9;
      *(uint32_t *)dest = local_3c;
      *(uint32_t *)((int)dest + uVar8) = local_6c;
      *(uint32_t *)((int)dest + uVar8 + 4) = local_68 | uVar1;
      local_6c = 0;
      dest = (char *)((int)dest + 8);
      local_68 = 0;
      local_3c = 0;
      local_38 = 0;
      }
      else {
      local_3c = local_3c >> 0x10 | local_38 << 0x10;
      local_38 = uVar9 >> 0x10;
      local_6c = local_6c >> 0x10 | local_68 << 0x10;
      local_68 = uVar1 >> 0x10;
      }
    }
    dest = (char *)((int)dest + uVar8);
    local_24 = local_24 - 1;
    uVar6 = uVar4;
    } while (local_24 != 0);
    local_24 = 0;
  }
  if (CompressedSpriteData[3] == 4) {
    uVar8 = local_60;
    for (iVar3 = (int)local_24 >> 1; uVar2 = uVar4, iVar3 != 0; iVar3 = iVar3 + -1) {
    while (uVar2 = uVar2 - 1, -1 < (int)uVar2) {
      local_60 = uVar8;
      if (local_48 == 0) {
      if (local_8c == 0) {
        local_84 = *local_90;
        local_80 = local_90[1];
        local_90 = local_90 + 2;
        local_8c = 0x40;
      }
      uVar6 = local_84 >> 1 | local_80 << 0x1f;
      local_80 = local_80 >> 1;
      local_8c = local_8c + -1;
      if ((local_84 & 1) == 0) {
        if (local_8c == 0) {
        local_8c = 0x40;
        uVar6 = *local_90;
        local_80 = local_90[1];
        local_90 = local_90 + 2;
        }
        uVar1 = uVar6 >> 1 | local_80 << 0x1f;
        local_80 = local_80 >> 1;
        local_8c = local_8c + -1;
        if ((uVar6 & 1) == 0) {
        if (local_8c == 0) {
          uVar1 = *local_90;
          local_80 = local_90[1];
          local_90 = local_90 + 2;
          local_8c = 0x40;
        }
        local_84 = uVar1 >> 1 | local_80 << 0x1f;
        uVar6 = local_80 >> 1;
        local_8c = local_8c + -1;
        if ((uVar1 & 1) != 0) {
          local_74 = uVar8;
          if (local_54 == 0) {
          local_54 = 0x10;
          local_74 = *local_88;
          local_5c = local_88[1];
          local_88 = local_88 + 2;
          }
          uVar8 = local_74 >> 4 | local_5c << 0x1c;
          local_74 = local_74 & 0xf;
          local_5c = local_5c >> 4;
          local_54 = local_54 + -1;
        }
        if (local_8c == 0) {
          local_8c = 0x40;
          local_84 = *local_90;
          uVar6 = local_90[1];
          local_90 = local_90 + 2;
        }
        local_80 = uVar6 >> 1;
        local_8c = local_8c + -1;
        if ((local_84 & 1) != 0) {
          local_7c = uVar8;
          if (local_54 == 0) {
          local_7c = *local_88;
          local_5c = local_88[1];
          local_88 = local_88 + 2;
          local_54 = 0x10;
          }
          uVar8 = local_7c >> 4 | local_5c << 0x1c;
          local_7c = local_7c & 0xf;
          local_5c = local_5c >> 4;
          local_54 = local_54 + -1;
        }
        if (local_54 == 0) {
          uVar8 = *local_88;
          local_5c = local_88[1];
          local_88 = local_88 + 2;
          local_54 = 0x10;
        }
        local_60 = uVar8 >> 4 | local_5c << 0x1c;
        local_5c = local_5c >> 4;
        local_54 = local_54 + -1;
        uVar1 = local_74;
        if ((uVar8 & 4) != 0) {
          uVar1 = local_7c;
        }
        uVar9 = local_74;
        if ((uVar8 & 8) != 0) {
          uVar9 = local_7c;
        }
        uVar9 = (uVar1 << 4 | uVar9) << 0x18;
        uVar1 = local_74;
        if ((uVar8 & 1) != 0) {
          uVar1 = local_7c;
        }
        uVar7 = local_74;
        if ((uVar8 & 2) != 0) {
          uVar7 = local_7c;
        }
        uVar1 = (uVar1 << 4 | uVar7) << 0x18;
        local_84 = local_84 >> 1 | uVar6 << 0x1f;
        }
        else {
        if (local_8c == 0) {
          uVar1 = *local_90;
          local_80 = local_90[1];
          local_90 = local_90 + 2;
          local_8c = 0x40;
        }
        uVar6 = uVar1 >> 1 | local_80 << 0x1f;
        local_80 = local_80 >> 1;
        local_8c = local_8c + -1;
        if ((uVar1 & 1) == 0) {
          if (local_8c == 0) {
          uVar6 = *local_90;
          local_80 = local_90[1];
          local_90 = local_90 + 2;
          local_8c = 0x40;
          }
          local_84 = uVar6 >> 1 | local_80 << 0x1f;
          local_80 = local_80 >> 1;
          local_8c = local_8c + -1;
          if ((uVar6 & 1) == 0) {
          uVar1 = (local_74 | local_74 << 4) << 0x18;
          uVar9 = uVar1;
          }
          else {
          uVar1 = (local_7c | local_7c << 4) << 0x18;
          uVar9 = uVar1;
          }
        }
        else {
          if (local_54 == 0) {
          local_54 = 0x10;
          uVar8 = *local_88;
          local_5c = local_88[1];
          local_88 = local_88 + 2;
          }
          uVar7 = local_5c << 0x1c;
          local_74 = uVar8 & 0xf;
          local_5c = local_5c >> 4;
          local_54 = local_54 + -1;
          uVar1 = (local_74 | local_74 << 4) << 0x18;
          uVar9 = uVar1;
          local_84 = uVar6;
          local_60 = uVar8 >> 4 | uVar7;
        }
        }
      }
      else {
        if (local_8c == 0) {
        local_8c = 0x40;
        uVar6 = *local_90;
        local_80 = local_90[1];
        local_90 = local_90 + 2;
        }
        uVar7 = uVar6 >> 1 | local_80 << 0x1f;
        local_80 = local_80 >> 1;
        local_8c = local_8c + -1;
        if ((uVar6 & 1) == 0) {
        if (local_8c == 0) {
          uVar7 = *local_90;
          local_80 = local_90[1];
          local_90 = local_90 + 2;
          local_8c = 0x40;
        }
        local_84 = uVar7 >> 1 | local_80 << 0x1f;
        local_80 = local_80 >> 1;
        local_8c = local_8c + -1;
        if ((uVar7 & 1) != 0) {
          if (local_20 == 0) {
          local_1c = *local_14;
          local_18 = local_14[1];
          local_14 = local_14 + 2;
          local_20 = 8;
          }
          uVar8 = local_18 << 0x18;
          local_18 = local_18 >> 8;
          local_20 = local_20 + -1;
          local_48 = (local_1c & 0xff) + 3;
          local_1c = local_1c >> 8 | uVar8;
        }
        }
        else {
        if (local_54 == 0) {
          uVar8 = *local_88;
          local_5c = local_88[1];
          local_88 = local_88 + 2;
          local_54 = 0x10;
        }
        uVar9 = uVar8 >> 4 | local_5c << 0x1c;
        local_5c = local_5c >> 4;
        local_54 = local_54 + -1;
        if (local_54 == 0) {
          uVar9 = *local_88;
          local_5c = local_88[1];
          local_88 = local_88 + 2;
          local_54 = 0x10;
        }
        uVar1 = uVar9 >> 4 | local_5c << 0x1c;
        local_5c = local_5c >> 4;
        local_54 = local_54 + -1;
        if (local_54 == 0) {
          uVar1 = *local_88;
          local_5c = local_88[1];
          local_88 = local_88 + 2;
          local_54 = 0x10;
        }
        uVar6 = uVar1 >> 4 | local_5c << 0x1c;
        uVar5 = local_5c >> 4;
        local_54 = local_54 + -1;
        if (local_54 == 0) {
          uVar6 = *local_88;
          uVar5 = local_88[1];
          local_88 = local_88 + 2;
          local_54 = 0x10;
        }
        local_5c = uVar5 >> 4;
        local_54 = local_54 + -1;
        local_74 = uVar9 & 0xf;
        uVar1 = (uVar1 & 0xf) << 0x18 | uVar6 << 0x1c;
        local_7c = uVar6 & 0xf;
        uVar9 = (uVar8 & 0xf) << 0x18 | uVar9 << 0x1c;
        local_84 = uVar7;
        local_60 = uVar6 >> 4 | uVar5 << 0x1c;
        }
      }
      }
      else {
      local_48 = local_48 + -1;
      }
      uVar8 = local_60;
      if ((uVar2 & 7) == 0) {
      *(uint32_t *)((int)dest + 4) = local_38 | uVar9;
      *(uint32_t *)dest = local_3c;
      *(uint32_t *)(uVar4 + (int)dest) = local_6c;
      *(uint32_t *)(uVar4 + 4 + (int)dest) = local_68 | uVar1;
      local_6c = 0;
      dest = (char *)((int)dest + 8);
      local_68 = 0;
      local_3c = 0;
      local_38 = 0;
      }
      else {
      local_3c = local_3c >> 8 | local_38 << 0x18;
      local_38 = (local_38 | uVar9) >> 8;
      local_6c = local_6c >> 8 | local_68 << 0x18;
      local_68 = (local_68 | uVar1) >> 8;
      }
    }
    dest = (char *)((int)dest + uVar4);
    }
  }
  }
  else {
    dest = decode_basic(CompressedSpriteData, dest);
  }

  auto width = ((uint16_t*)data.data())[3];
  auto height = ((uint16_t*)data.data())[4];
  
  std::vector<unsigned char> pixels(origPos, origPos + width * height);

  if (((uint16_t*)data.data())[2] == 4)
  {
      for (auto& pixel : pixels)
      {
          pixel = (pixel << 4) | (pixel >> 4);
      }
  }

  std::ofstream output_file(std::string(name) + ".raw", std::ios::out | std::ios::binary);
  output_file.write((const char*)&pixels[0], pixels.size());

  unsigned int error = lodepng::encode((std::string(name) + ".png").c_str(), pixels, static_cast<uint32_t>(width), static_cast<uint32_t>(height), LodePNGColorType::LCT_GREY, ((uint16_t*)data.data())[2]);
  if (error) std::cout << "encoder error " << error << ": " << lodepng_error_text(error) << std::endl;
}

int main(const int argc, const char *argv[])
{
  if (argc <= 1)
  {
    std::cerr << "xx_spritedecode <filename1> <filename2> etc" << std::endl;
    return EXIT_FAILURE;
  }

  for (auto i = 1; i < argc; i++)
  decode(argv[i]);

  return 0;
}