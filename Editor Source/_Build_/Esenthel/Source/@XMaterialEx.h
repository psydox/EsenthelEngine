﻿/******************************************************************************/
/******************************************************************************/
// MATERIAL
/******************************************************************************/
class XMaterialEx : XMaterial
{
   Image    base_0, base_1, base_2, detail, macro, emissive_img;
   UID      base_0_id, base_1_id, base_2_id, detail_id, macro_id, emissive_id;
   bool     adjust_params;
   TEX_FLAG textures;

   void create(C Material &src);

public:
   XMaterialEx();
};
/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
