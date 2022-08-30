#include "..\Public\Transform.h"

CTransform::CTransform(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CComponent(pGraphic_Device)
{

}

CTransform::CTransform(const CTransform & rhs)
	: CComponent(rhs)
	, m_WorldMatrix(rhs.m_WorldMatrix)
{

}

_float3 CTransform::Get_Scale()
{
	_float3		vRight = Get_State(CTransform::STATE_RIGHT);
	_float3		vUp = Get_State(CTransform::STATE_UP);
	_float3		vLook = Get_State(CTransform::STATE_LOOK);

	return _float3(D3DXVec3Length(&vRight), D3DXVec3Length(&vUp), D3DXVec3Length(&vLook));
}

_float CTransform::Get_ScaleX()
{
	_float3		vRight = Get_State(CTransform::STATE_RIGHT);

	return vRight.x;
}

void CTransform::Set_Scaled(_float3 vScale)
{
	_float3		vRight = Get_State(CTransform::STATE_RIGHT);
	_float3		vUp = Get_State(CTransform::STATE_UP);
	_float3		vLook = Get_State(CTransform::STATE_LOOK);

	Set_State(CTransform::STATE_RIGHT, *D3DXVec3Normalize(&vRight, &vRight) * vScale.x);
	Set_State(CTransform::STATE_UP, *D3DXVec3Normalize(&vUp, &vUp) * vScale.y);
	Set_State(CTransform::STATE_LOOK, *D3DXVec3Normalize(&vLook, &vLook) * vScale.z);
}

HRESULT CTransform::Initialize_Prototype()
{
	D3DXMatrixIdentity(&m_WorldMatrix);

	return S_OK;
}

HRESULT CTransform::Initialize(void * pArg)
{
	if (nullptr != pArg)
		memcpy(&m_TransformDesc, pArg, sizeof(TRANSFORMDESC));

	return S_OK;
}

HRESULT CTransform::Bind_OnGraphicDev()
{
	if (nullptr == m_pGraphic_Device)
		return E_FAIL;

	m_pGraphic_Device->SetTransform(D3DTS_WORLD, &m_WorldMatrix);

	return S_OK;
}

void CTransform::Go_Straight(_float fTimeDelta)
{
	_float3		vPosition = Get_State(CTransform::STATE_POSITION);
	_float3		vLook = Get_State(CTransform::STATE_LOOK);

	vPosition += *D3DXVec3Normalize(&vLook, &vLook) * m_TransformDesc.fSpeedPerSec * fTimeDelta;

	Set_State(CTransform::STATE_POSITION, vPosition);
}

void CTransform::Go_Backward(_float fTimeDelta)
{
	_float3		vPosition = Get_State(CTransform::STATE_POSITION);
	_float3		vLook = Get_State(CTransform::STATE_LOOK);

	vPosition -= *D3DXVec3Normalize(&vLook, &vLook) * m_TransformDesc.fSpeedPerSec * fTimeDelta;

	Set_State(CTransform::STATE_POSITION, vPosition);
}

void CTransform::Go_Right(_float fTimeDelta)
{
	_float3		vPosition = Get_State(CTransform::STATE_POSITION);
	_float3		vRight = Get_State(CTransform::STATE_RIGHT);

	vPosition += *D3DXVec3Normalize(&vRight, &vRight) * m_TransformDesc.fSpeedPerSec * fTimeDelta;

	Set_State(CTransform::STATE_POSITION, vPosition);
}

void CTransform::Go_Left(_float fTimeDelta)
{
	_float3		vPosition = Get_State(CTransform::STATE_POSITION);
	_float3		vRight = Get_State(CTransform::STATE_RIGHT);

	vPosition -= *D3DXVec3Normalize(&vRight, &vRight) * m_TransformDesc.fSpeedPerSec * fTimeDelta;

	Set_State(CTransform::STATE_POSITION, vPosition);
}

void CTransform::Turn(_float3 vAxis, _float fTimeDelta)
{
	_float3	vRight = Get_State(CTransform::STATE_RIGHT);
	_float3	vUp = Get_State(CTransform::STATE_UP);
	_float3	vLook = Get_State(CTransform::STATE_LOOK);

	_float4x4	RotationMatrix;
	D3DXMatrixRotationAxis(&RotationMatrix, &vAxis, m_TransformDesc.fRotationPerSec * fTimeDelta);

	D3DXVec3TransformNormal(&vRight, &vRight, &RotationMatrix);
	D3DXVec3TransformNormal(&vUp, &vUp, &RotationMatrix);
	D3DXVec3TransformNormal(&vLook, &vLook, &RotationMatrix);

	Set_State(CTransform::STATE_RIGHT, vRight);
	Set_State(CTransform::STATE_UP, vUp);
	Set_State(CTransform::STATE_LOOK, vLook);
}


void CTransform::Up(_float fTimeDelta)
{
	_float3		vPosition = Get_State(CTransform::STATE_POSITION);
	_float3		vUp = Get_State(CTransform::STATE_UP);

	m_TransformDesc.fSpeedPerSec = 9.8f;

	vPosition += *D3DXVec3Normalize(&vUp, &vUp) * m_TransformDesc.fSpeedPerSec * fTimeDelta;

	Set_State(CTransform::STATE_POSITION, vPosition);
}

void CTransform::Down(_float fTimeDelta)
{
	_float3		vPosition = Get_State(CTransform::STATE_POSITION);
	_float3		vUp = Get_State(CTransform::STATE_UP);

	vPosition -= *D3DXVec3Normalize(&vUp, &vUp) * m_TransformDesc.fSpeedPerSec * fTimeDelta;

	Set_State(CTransform::STATE_POSITION, vPosition);
}

void CTransform::Fall(_float fTimeDelta)
{
	_float3		vPosition = Get_State(CTransform::STATE_POSITION);
	_float3		vUp = Get_State(CTransform::STATE_UP);

	vPosition -= *D3DXVec3Normalize(&vUp, &vUp) * m_TransformDesc.fSpeedPerSec * fTimeDelta*m_fGravity*m_fGravity;

	Set_State(CTransform::STATE_POSITION, vPosition);
}

void CTransform::Go_RT(_float fTimeDelta)
{
	_float3		vPosition = Get_State(CTransform::STATE_POSITION);
	_float3		vRight = Get_State(CTransform::STATE_RIGHT);
	_float3		vLook = Get_State(CTransform::STATE_LOOK);

	_float3		fx = *D3DXVec3Normalize(&vRight, &vRight) * m_TransformDesc.fSpeedPerSec * fTimeDelta;
	_float3     fz = *D3DXVec3Normalize(&vLook, &vLook) * m_TransformDesc.fSpeedPerSec * fTimeDelta;

	vPosition += (_float3(sqrtf(fx.x*fx.x),sqrtf(fx.y*fx.y), sqrtf(fx.z*fx.z))+ _float3(sqrtf(fz.x*fz.x), sqrtf(fz.y*fz.y), sqrtf(fz.z*fz.z)));

	Set_State(CTransform::STATE_POSITION, vPosition);
}

void CTransform::Go_LT(_float fTimeDelta)
{
	_float3		vPosition = Get_State(CTransform::STATE_POSITION);
	_float3		vRight = Get_State(CTransform::STATE_RIGHT);
	_float3		vLook = Get_State(CTransform::STATE_LOOK);

	_float3		fx = *D3DXVec3Normalize(&vRight, &vRight) * m_TransformDesc.fSpeedPerSec * fTimeDelta;
	_float3     fz = *D3DXVec3Normalize(&vLook, &vLook) * m_TransformDesc.fSpeedPerSec * fTimeDelta;

	vPosition += (-_float3(sqrtf(fx.x*fx.x), sqrtf(fx.y*fx.y), sqrtf(fx.z*fx.z)) + _float3(sqrtf(fz.x*fz.x), sqrtf(fz.y*fz.y), sqrtf(fz.z*fz.z)));

	Set_State(CTransform::STATE_POSITION, vPosition);
}

void CTransform::Go_LD(_float fTimeDelta)
{
}

void CTransform::Go_RD(_float fTimeDelta)
{
}

void CTransform::Jump(_float fTimeDelta, _float fJumpPower, _float fFallSpeed)
{
	_float3		vPosition = Get_State(CTransform::STATE_POSITION);
	_float3		vUp = Get_State(CTransform::STATE_UP);

	vPosition += *D3DXVec3Normalize(&vUp, &vUp) * m_TransformDesc.fSpeedPerSec * fTimeDelta * fJumpPower -
		*D3DXVec3Normalize(&vUp, &vUp) * m_TransformDesc.fSpeedPerSec * fTimeDelta*fFallSpeed/**fFallSpeed*/;

	Set_State(CTransform::STATE_POSITION, vPosition);
}

_float3 CTransform::Save_Collision_Pos(_float _fTimeDelta)
{
	m_fSavePos = Get_State(CTransform::STATE_POSITION);

	if (!m_bJump && !m_bJump)
		m_bSecSave = true;

	return m_fSavePos;
}

void CTransform::Attacked_Move(_float3 vcolPos, _float fTimeDelta)
{
	_float3 vPos = Get_State(STATE_POSITION);

	_float3 vLook = vPos-vcolPos;

	vPos += *D3DXVec3Normalize(&vLook, &vLook)*fTimeDelta*m_TransformDesc.fSpeedPerSec;

	Set_State(STATE_POSITION, vPos);
}

void CTransform::LookAt(_float3 vPoint)
{
	_float3		vPosition = Get_State(CTransform::STATE_POSITION);

	_float3		vLook = vPoint - vPosition;

	_float3		vRight = *D3DXVec3Cross(&vRight, &_float3(0.f, 1.f, 0.f), &vLook);

	_float3		vUp = *D3DXVec3Cross(&vUp, &vLook, &vRight);

	_float3		vScale = Get_Scale();

	Set_State(CTransform::STATE_RIGHT, *D3DXVec3Normalize(&vRight, &vRight) * vScale.x);
	Set_State(CTransform::STATE_UP, *D3DXVec3Normalize(&vUp, &vUp) * vScale.y);
	Set_State(CTransform::STATE_LOOK, *D3DXVec3Normalize(&vLook, &vLook) * vScale.z);
}


CTransform * CTransform::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CTransform*	pInstance = new CTransform(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		ERR_MSG(TEXT("Failed to Created : CTransform"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent * CTransform::Clone(void* pArg)
{
	CTransform*	pInstance = new CTransform(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		ERR_MSG(TEXT("Failed to Cloned : CTransform"));
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CTransform::Free()
{
	__super::Free();

}
