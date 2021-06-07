//
#pragma once

#include "LightEngine.h"


class RenderStateMgr
{
private:
    LEIDeviceObject* _dev_obj;
    LEIRenderStateAtomSet* _rsa_scene;
    LEIRenderStateAtomSet* _rsa_cha;
    LEIRenderStateAtomSet* _rsa_sceneobj;
    LEIRenderStateAtomSet* _rsa_sceneitem;
    LEIRenderStateAtomSet* _rsa_terrain;
    LEIRenderStateAtomSet* _rsa_transpobj;

    D3DLIGHTX _scnobj_lgt;
    D3DLIGHTX _scnobj_lgt_old[3];
    BOOL _scnobj_lgt_enable_old[3];

    D3DLIGHTX _cha_lgt;
    D3DLIGHTX _cha_lgt_old;
    BOOL _cha_lgt_enable_old;

public:
    RenderStateMgr();
    ~RenderStateMgr();

    HRESULT Init(LEIDeviceObject* dev_obj);

    HRESULT BeginScene();
    HRESULT BeginCharacter();
    HRESULT BeginSceneObject();
    HRESULT BeginSceneItem();
    HRESULT BeginTerrain();
    HRESULT BeginTranspObject();
    HRESULT EndScene();
    HRESULT EndCharacter();
    HRESULT EndSceneObject();
    HRESULT EndSceneItem();
    HRESULT EndTerrain();
    HRESULT EndTranspObject();

};
