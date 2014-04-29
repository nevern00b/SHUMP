#include "DataManager.h"

#include "Utils.h"
#include "Rendering/Mesh.h"
#include "Rendering/ShaderCommon.h"
#include "Globals.h"
#include "Rendering/RenderManager.h"
#include "Rendering/Material.h"

DataManager::DataManager()
{
    // Create cube primitive
    float vertices[192] = { -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f, 0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.5f, 0.5f, -0.5f, 1.0f, 0.0f, -0.0f, 0.0f, 1.0f, 0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, -0.0f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, -0.0f, 1.0f, 1.0f, 0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f };
    ushort indices[36] = { 0, 1, 2, 0, 2, 3, 4, 5, 6, 4, 6, 7, 8, 9, 10, 8, 10, 11, 12, 13, 14, 12, 14, 15, 16, 17, 18, 16, 18, 19, 20, 21, 22, 20, 22, 23 };
	Mesh* cubeMesh = new Mesh(vertices, indices, 24, 36);
    m_meshes["cube"] = cubeMesh;

	float sphereVerts[1296] = { 0.0f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.10159f, -0.483975f, 0.0738089f, 0.210944f, -0.965392f, 0.153264f, 0.0f, 1.0f, -0.0388033f, -0.483975f, 0.119426f, -0.0805689f, -0.965392f, 0.247963f, 0.0f, 1.0f, 0.361804f, -0.22361f, 0.262863f, 0.723594f, -0.447218f, 0.525712f, 0.0f, 1.0f, 0.304773f, -0.328759f, 0.221428f, 0.604205f, -0.664968f, 0.438978f, 0.0f, 1.0f, 0.406365f, -0.25115f, 0.147619f, 0.81518f, -0.5038f, 0.285714f, 0.0f, 1.0f, -0.125574f, -0.483974f, 0.0f, -0.26075f, -0.965392f, 0.0f, 0.0f, 1.0f, -0.0388033f, -0.483975f, -0.119426f, -0.0805689f, -0.965392f, -0.247963f, 0.0f, 1.0f, 0.10159f, -0.483975f, -0.0738089f, 0.210944f, -0.965392f, -0.153264f, 0.0f, 1.0f, 0.430349f, -0.125575f, 0.221429f, 0.864986f, -0.243049f, 0.438978f, 0.0f, 1.0f, -0.138194f, -0.22361f, 0.425325f, -0.276376f, -0.447218f, 0.850643f, 0.0f, 1.0f, -0.0148196f, -0.251151f, 0.432092f, -0.019837f, -0.5038f, 0.863552f, 0.0f, 1.0f, -0.0776075f, -0.125576f, 0.477711f, -0.150212f, -0.243049f, 0.958281f, 0.0f, 1.0f, -0.447213f, -0.223608f, 0.0f, -0.894406f, -0.447188f, 0.0f, 0.0f, 1.0f, -0.415525f, -0.251149f, 0.119427f, -0.827448f, -0.5038f, 0.247963f, 0.0f, 1.0f, -0.478313f, -0.125575f, 0.0738091f, -0.957823f, -0.243049f, 0.153264f, 0.0f, 1.0f, -0.138194f, -0.22361f, -0.425325f, -0.276376f, -0.447218f, -0.850643f, 0.0f, 1.0f, -0.241986f, -0.251151f, -0.358282f, -0.491531f, -0.5038f, -0.710288f, 0.0f, 1.0f, -0.218003f, -0.125576f, -0.432094f, -0.441725f, -0.243049f, -0.863582f, 0.0f, 1.0f, 0.361804f, -0.22361f, -0.262863f, 0.723594f, -0.447218f, -0.525712f, 0.0f, 1.0f, 0.26597f, -0.251151f, -0.340856f, 0.523637f, -0.5038f, -0.686972f, 0.0f, 1.0f, 0.343579f, -0.125576f, -0.340858f, 0.684805f, -0.243049f, -0.686972f, 0.0f, 1.0f, 0.343579f, -0.125576f, 0.340858f, 0.684805f, -0.243049f, 0.686972f, 0.0f, 1.0f, -0.218003f, -0.125576f, 0.432094f, -0.441725f, -0.243049f, 0.863582f, 0.0f, 1.0f, -0.478313f, -0.125575f, -0.0738091f, -0.957823f, -0.243049f, -0.153264f, 0.0f, 1.0f, -0.0776075f, -0.125576f, -0.477711f, -0.150212f, -0.243049f, -0.958281f, 0.0f, 1.0f, 0.430349f, -0.125575f, -0.221429f, 0.864986f, -0.243049f, -0.438978f, 0.0f, 1.0f, 0.138194f, 0.22361f, 0.425325f, 0.276376f, 0.447218f, 0.850643f, 0.0f, 1.0f, 0.241986f, 0.251151f, 0.358282f, 0.491531f, 0.5038f, 0.710288f, 0.0f, 1.0f, 0.116411f, 0.32876f, 0.358282f, 0.230781f, 0.664968f, 0.710288f, 0.0f, 1.0f, -0.361804f, 0.22361f, 0.262863f, -0.723594f, 0.447218f, 0.525712f, 0.0f, 1.0f, -0.26597f, 0.251151f, 0.340856f, -0.523637f, 0.5038f, 0.686972f, 0.0f, 1.0f, -0.304773f, 0.328759f, 0.221428f, -0.604205f, 0.664968f, 0.438978f, 0.0f, 1.0f, -0.361804f, 0.22361f, -0.262863f, -0.723594f, 0.447218f, -0.525712f, 0.0f, 1.0f, -0.406365f, 0.25115f, -0.147619f, -0.81518f, 0.5038f, -0.285714f, 0.0f, 1.0f, -0.304773f, 0.328759f, -0.221428f, -0.604205f, 0.664968f, -0.438978f, 0.0f, 1.0f, 0.138194f, 0.22361f, -0.425325f, 0.276376f, 0.447218f, -0.850643f, 0.0f, 1.0f, 0.0148196f, 0.251151f, -0.432092f, 0.019837f, 0.5038f, -0.863552f, 0.0f, 1.0f, 0.116411f, 0.32876f, -0.358282f, 0.230781f, 0.664968f, -0.710288f, 0.0f, 1.0f, 0.447213f, 0.223608f, 0.0f, 0.894406f, 0.447188f, 0.0f, 0.0f, 1.0f, 0.415525f, 0.251149f, -0.119427f, 0.827448f, 0.5038f, -0.247963f, 0.0f, 1.0f, 0.376721f, 0.328757f, 0.0f, 0.746849f, 0.664968f, 0.0f, 0.0f, 1.0f, -0.116411f, -0.32876f, 0.358282f, -0.230781f, -0.664968f, 0.710288f, 0.0f, 1.0f, -0.0812278f, -0.425327f, 0.249998f, -0.16245f, -0.850643f, 0.499985f, 0.0f, 1.0f, 0.0263951f, -0.361806f, 0.344093f, 0.0592059f, -0.727531f, 0.683493f, 0.0f, 1.0f, 0.0690993f, -0.447215f, 0.21266f, 0.140629f, -0.890408f, 0.432844f, 0.0f, 1.0f, 0.131434f, -0.262869f, 0.404506f, 0.262856f, -0.525712f, 0.808985f, 0.0f, 1.0f, 0.180902f, -0.361805f, 0.29389f, 0.353832f, -0.727531f, 0.587756f, 0.0f, 1.0f, 0.26597f, -0.251151f, 0.340856f, 0.523637f, -0.5038f, 0.686972f, 0.0f, 1.0f, 0.212661f, -0.425327f, 0.154506f, 0.425306f, -0.850643f, 0.309f, 0.0f, 1.0f, 0.406365f, -0.25115f, -0.147619f, 0.81518f, -0.5038f, -0.285714f, 0.0f, 1.0f, 0.304773f, -0.328759f, -0.221428f, 0.604205f, -0.664968f, -0.438978f, 0.0f, 1.0f, 0.425324f, -0.262868f, 0.0f, 0.850643f, -0.525712f, 0.0f, 0.0f, 1.0f, 0.335409f, -0.361805f, -0.0812284f, 0.668325f, -0.727531f, -0.154881f, 0.0f, 1.0f, 0.335409f, -0.361805f, 0.0812289f, 0.668325f, -0.727531f, 0.154881f, 0.0f, 1.0f, 0.212661f, -0.425327f, -0.154506f, 0.425306f, -0.850643f, -0.309f, 0.0f, 1.0f, 0.223605f, -0.447214f, 3.68978e-007f, 0.455123f, -0.890408f, 0.0f, 0.0f, 1.0f, -0.376721f, -0.328757f, 0.0f, -0.746849f, -0.664968f, 0.0f, 0.0f, 1.0f, -0.262865f, -0.425326f, 0.0f, -0.525712f, -0.850643f, 0.0f, 0.0f, 1.0f, -0.319097f, -0.361805f, 0.131432f, -0.631733f, -0.727531f, 0.267495f, 0.0f, 1.0f, -0.180901f, -0.447214f, 0.131432f, -0.368206f, -0.890408f, 0.267495f, 0.0f, 1.0f, -0.344095f, -0.262868f, 0.249998f, -0.688162f, -0.525712f, 0.499985f, 0.0f, 1.0f, -0.223605f, -0.361805f, 0.262864f, -0.449629f, -0.727531f, 0.518143f, 0.0f, 1.0f, -0.241986f, -0.251151f, 0.358282f, -0.491531f, -0.5038f, 0.710288f, 0.0f, 1.0f, -0.116411f, -0.32876f, -0.358282f, -0.230781f, -0.664968f, -0.710288f, 0.0f, 1.0f, -0.0812278f, -0.425327f, -0.249998f, -0.16245f, -0.850643f, -0.499985f, 0.0f, 1.0f, -0.223605f, -0.361806f, -0.262863f, -0.449629f, -0.727531f, -0.518143f, 0.0f, 1.0f, -0.180901f, -0.447214f, -0.131431f, -0.368206f, -0.890408f, -0.267495f, 0.0f, 1.0f, -0.344095f, -0.262868f, -0.249998f, -0.688162f, -0.525712f, -0.499985f, 0.0f, 1.0f, -0.319097f, -0.361805f, -0.131431f, -0.631733f, -0.727531f, -0.267495f, 0.0f, 1.0f, -0.415525f, -0.251149f, -0.119427f, -0.827448f, -0.5038f, -0.247963f, 0.0f, 1.0f, 0.180902f, -0.361806f, -0.29389f, 0.353832f, -0.727531f, -0.587756f, 0.0f, 1.0f, 0.0690984f, -0.447215f, -0.212661f, 0.140629f, -0.890408f, -0.432844f, 0.0f, 1.0f, 0.131434f, -0.262869f, -0.404506f, 0.262856f, -0.525712f, -0.808985f, 0.0f, 1.0f, 0.0263945f, -0.361805f, -0.344093f, 0.0592059f, -0.727531f, -0.683493f, 0.0f, 1.0f, -0.0148196f, -0.251151f, -0.432092f, -0.019837f, -0.5038f, -0.863552f, 0.0f, 1.0f, 0.478313f, 0.125575f, 0.0738091f, 0.957823f, 0.243049f, 0.153264f, 0.0f, 1.0f, 0.478313f, 0.125575f, -0.0738091f, 0.957823f, 0.243049f, -0.153264f, 0.0f, 1.0f, 0.475529f, 0.0f, 0.154506f, 0.951048f, 0.0f, 0.309f, 0.0f, 1.0f, 0.5f, 0.0f, 0.0f, 0.999939f, -0.00885034f, 0.0f, 0.0f, 1.0f, 0.473607f, -0.138198f, 0.0812287f, 0.949614f, -0.272408f, 0.154881f, 0.0f, 1.0f, 0.475529f, 0.0f, -0.154506f, 0.951048f, 0.0f, -0.309f, 0.0f, 1.0f, 0.473607f, -0.138198f, -0.0812288f, 0.949614f, -0.272408f, -0.154881f, 0.0f, 1.0f, 0.0776075f, 0.125576f, 0.477711f, 0.150212f, 0.243049f, 0.958281f, 0.0f, 1.0f, 0.218003f, 0.125576f, 0.432094f, 0.441725f, 0.243049f, 0.863582f, 0.0f, 1.0f, 0.0f, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.154509f, 0.0f, 0.475528f, 0.309f, -0.00885034f, 0.951018f, 0.0f, 1.0f, 0.0690995f, -0.138199f, 0.475527f, 0.146123f, -0.272408f, 0.950987f, 0.0f, 1.0f, 0.293893f, 0.0f, 0.404508f, 0.587756f, 0.0f, 0.809015f, 0.0f, 1.0f, 0.223608f, -0.138199f, 0.425324f, 0.440748f, -0.272408f, 0.855251f, 0.0f, 1.0f, -0.430349f, 0.125575f, 0.221429f, -0.864986f, 0.243049f, 0.438978f, 0.0f, 1.0f, -0.343579f, 0.125576f, 0.340858f, -0.684805f, 0.243049f, 0.686972f, 0.0f, 1.0f, -0.475529f, 0.0f, 0.154506f, -0.951048f, 0.0f, 0.309f, 0.0f, 1.0f, -0.404509f, 0.0f, 0.293892f, -0.808985f, -0.00885034f, 0.587756f, 0.0f, 1.0f, -0.430902f, -0.138198f, 0.212662f, -0.85931f, -0.272408f, 0.432844f, 0.0f, 1.0f, -0.293893f, 0.0f, 0.404508f, -0.587756f, 0.0f, 0.809015f, 0.0f, 1.0f, -0.335409f, -0.138199f, 0.344095f, -0.677206f, -0.272408f, 0.683493f, 0.0f, 1.0f, -0.343579f, 0.125576f, -0.340858f, -0.684805f, 0.243049f, -0.686972f, 0.0f, 1.0f, -0.430349f, 0.125575f, -0.221429f, -0.864986f, 0.243049f, -0.438978f, 0.0f, 1.0f, -0.293893f, 0.0f, -0.404508f, -0.587756f, 0.0f, -0.809015f, 0.0f, 1.0f, -0.404509f, 0.0f, -0.293892f, -0.808985f, -0.00885034f, -0.587756f, 0.0f, 1.0f, -0.335409f, -0.138199f, -0.344095f, -0.677206f, -0.272408f, -0.683493f, 0.0f, 1.0f, -0.475529f, 0.0f, -0.154506f, -0.951048f, 0.0f, -0.309f, 0.0f, 1.0f, -0.430901f, -0.138198f, -0.212662f, -0.85931f, -0.272408f, -0.432844f, 0.0f, 1.0f, 0.218003f, 0.125576f, -0.432094f, 0.441725f, 0.243049f, -0.863582f, 0.0f, 1.0f, 0.0776075f, 0.125576f, -0.477711f, 0.150212f, 0.243049f, -0.958281f, 0.0f, 1.0f, 0.293893f, 0.0f, -0.404508f, 0.587756f, 0.0f, -0.809015f, 0.0f, 1.0f, 0.154509f, 0.0f, -0.475528f, 0.309f, -0.00885034f, -0.951018f, 0.0f, 1.0f, 0.223608f, -0.138199f, -0.425324f, 0.440748f, -0.272408f, -0.855251f, 0.0f, 1.0f, 0.0f, 0.0f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0690995f, -0.138199f, -0.475527f, 0.146123f, -0.272408f, -0.950987f, 0.0f, 1.0f, 0.33541f, 0.138198f, 0.344095f, 0.677206f, 0.272408f, 0.683493f, 0.0f, 1.0f, 0.404509f, -9.51145e-007f, 0.293891f, 0.808985f, 0.00885034f, 0.587756f, 0.0f, 1.0f, 0.344095f, 0.262868f, 0.249998f, 0.688162f, 0.525712f, 0.499985f, 0.0f, 1.0f, 0.430902f, 0.138197f, 0.212662f, 0.85931f, 0.272408f, 0.432844f, 0.0f, 1.0f, 0.415525f, 0.251149f, 0.119427f, 0.827448f, 0.5038f, 0.247963f, 0.0f, 1.0f, -0.223608f, 0.138198f, 0.425324f, -0.440748f, 0.272408f, 0.855251f, 0.0f, 1.0f, -0.154509f, -3.93577e-007f, 0.475528f, -0.309f, 0.00885034f, 0.951018f, 0.0f, 1.0f, -0.131434f, 0.262869f, 0.404506f, -0.262856f, 0.525712f, 0.808985f, 0.0f, 1.0f, -0.0690996f, 0.138198f, 0.475527f, -0.146123f, 0.272408f, 0.950987f, 0.0f, 1.0f, 0.0148196f, 0.251151f, 0.432092f, 0.019837f, 0.5038f, 0.863552f, 0.0f, 1.0f, -0.473607f, 0.138198f, -0.0812288f, -0.949614f, 0.272408f, -0.154881f, 0.0f, 1.0f, -0.5f, 3.11582e-007f, 1.8039e-007f, -0.999939f, 0.00885034f, 0.0f, 0.0f, 1.0f, -0.425324f, 0.262868f, 0.0f, -0.850643f, 0.525712f, 0.0f, 0.0f, 1.0f, -0.473606f, 0.138198f, 0.0812289f, -0.949614f, 0.272408f, 0.154881f, 0.0f, 1.0f, -0.406365f, 0.25115f, 0.147619f, -0.81518f, 0.5038f, 0.285714f, 0.0f, 1.0f, -0.0690992f, 0.138198f, -0.475527f, -0.146123f, 0.272408f, -0.950987f, 0.0f, 1.0f, -0.154508f, -2.45986e-007f, -0.475528f, -0.309f, 0.00885034f, -0.951018f, 0.0f, 1.0f, -0.131434f, 0.262869f, -0.404506f, -0.262856f, 0.525712f, -0.808985f, 0.0f, 1.0f, -0.223607f, 0.138199f, -0.425324f, -0.440748f, 0.272408f, -0.855251f, 0.0f, 1.0f, -0.26597f, 0.251151f, -0.340856f, -0.523637f, 0.5038f, -0.686972f, 0.0f, 1.0f, 0.430902f, 0.138198f, -0.212661f, 0.85931f, 0.272408f, -0.432844f, 0.0f, 1.0f, 0.40451f, 0.0f, -0.293891f, 0.808985f, 0.00885034f, -0.587756f, 0.0f, 1.0f, 0.344095f, 0.262868f, -0.249998f, 0.688162f, 0.525712f, -0.499985f, 0.0f, 1.0f, 0.33541f, 0.138199f, -0.344095f, 0.677206f, 0.272408f, -0.683493f, 0.0f, 1.0f, 0.241986f, 0.251151f, -0.358282f, 0.491531f, 0.5038f, -0.710288f, 0.0f, 1.0f, 0.0388033f, 0.483975f, 0.119426f, 0.0805689f, 0.965392f, 0.247963f, 0.0f, 1.0f, 0.125574f, 0.483974f, 0.0f, 0.26075f, 0.965392f, 0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0812278f, 0.425327f, 0.249998f, 0.16245f, 0.850643f, 0.499985f, 0.0f, 1.0f, 0.1809f, 0.447215f, 0.131432f, 0.368206f, 0.890408f, 0.267495f, 0.0f, 1.0f, 0.223605f, 0.361806f, 0.262864f, 0.449629f, 0.727531f, 0.518143f, 0.0f, 1.0f, 0.262865f, 0.425326f, 0.0f, 0.525712f, 0.850643f, 0.0f, 0.0f, 1.0f, 0.319097f, 0.361805f, 0.131432f, 0.631733f, 0.727531f, 0.267495f, 0.0f, 1.0f, -0.10159f, 0.483975f, 0.0738089f, -0.210944f, 0.965392f, 0.153264f, 0.0f, 1.0f, -0.212661f, 0.425327f, 0.154506f, -0.425306f, 0.850643f, 0.309f, 0.0f, 1.0f, -0.0690987f, 0.447215f, 0.21266f, -0.140629f, 0.890408f, 0.432844f, 0.0f, 1.0f, -0.180902f, 0.361806f, 0.293889f, -0.353832f, 0.727531f, 0.587726f, 0.0f, 1.0f, -0.0263948f, 0.361806f, 0.344092f, -0.0592059f, 0.727531f, 0.683493f, 0.0f, 1.0f, -0.10159f, 0.483975f, -0.0738089f, -0.210944f, 0.965392f, -0.153264f, 0.0f, 1.0f, -0.212661f, 0.425327f, -0.154506f, -0.425306f, 0.850643f, -0.309f, 0.0f, 1.0f, -0.223605f, 0.447215f, 0.0f, -0.455123f, 0.890408f, 0.0f, 0.0f, 1.0f, -0.335408f, 0.361805f, -0.0812285f, -0.668325f, 0.727531f, -0.154881f, 0.0f, 1.0f, -0.335408f, 0.361805f, 0.0812285f, -0.668325f, 0.727531f, 0.154881f, 0.0f, 1.0f, 0.0388033f, 0.483975f, -0.119426f, 0.0805689f, 0.965392f, -0.247963f, 0.0f, 1.0f, 0.0812278f, 0.425327f, -0.249998f, 0.16245f, 0.850643f, -0.499985f, 0.0f, 1.0f, -0.0690986f, 0.447215f, -0.21266f, -0.140629f, 0.890408f, -0.432844f, 0.0f, 1.0f, -0.0263948f, 0.361806f, -0.344092f, -0.0592059f, 0.727531f, -0.683493f, 0.0f, 1.0f, -0.180902f, 0.361806f, -0.293889f, -0.353832f, 0.727531f, -0.587726f, 0.0f, 1.0f, 0.1809f, 0.447215f, -0.131432f, 0.368206f, 0.890408f, -0.267495f, 0.0f, 1.0f, 0.319097f, 0.361805f, -0.131432f, 0.631733f, 0.727531f, -0.267495f, 0.0f, 1.0f, 0.223605f, 0.361806f, -0.262864f, 0.449629f, 0.727531f, -0.518143f, 0.0f, 1.0f };
	ushort sphereIndices[960] = { 0, 1, 2, 3, 4, 5, 0, 2, 6, 0, 6, 7, 0, 7, 8, 3, 5, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 3, 9, 22, 10, 12, 23, 13, 15, 24, 16, 18, 25, 19, 21, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 11, 10, 43, 44, 42, 2, 45, 43, 42, 44, 11, 44, 46, 11, 43, 45, 44, 45, 47, 44, 44, 47, 46, 47, 48, 46, 2, 1, 45, 1, 49, 45, 45, 49, 47, 49, 4, 47, 47, 4, 48, 4, 3, 48, 50, 51, 19, 52, 53, 50, 5, 54, 52, 50, 53, 51, 53, 55, 51, 52, 54, 53, 54, 56, 53, 53, 56, 55, 56, 8, 55, 5, 4, 54, 4, 49, 54, 54, 49, 56, 49, 1, 56, 56, 1, 8, 1, 0, 8, 57, 14, 13, 58, 59, 57, 6, 60, 58, 57, 59, 14, 59, 61, 14, 58, 60, 59, 60, 62, 59, 59, 62, 61, 62, 63, 61, 6, 2, 60, 2, 43, 60, 60, 43, 62, 43, 42, 62, 62, 42, 63, 42, 10, 63, 64, 17, 16, 65, 66, 64, 7, 67, 65, 64, 66, 17, 66, 68, 17, 65, 67, 66, 67, 69, 66, 66, 69, 68, 69, 70, 68, 7, 6, 67, 6, 58, 67, 67, 58, 69, 58, 57, 69, 69, 57, 70, 57, 13, 70, 51, 20, 19, 55, 71, 51, 8, 72, 55, 51, 71, 20, 71, 73, 20, 55, 72, 71, 72, 74, 71, 71, 74, 73, 74, 75, 73, 8, 7, 72, 7, 65, 72, 72, 65, 74, 65, 64, 74, 74, 64, 75, 64, 16, 75, 76, 77, 39, 78, 79, 76, 9, 80, 78, 76, 79, 77, 79, 81, 77, 78, 80, 79, 80, 82, 79, 79, 82, 81, 82, 26, 81, 9, 5, 80, 5, 52, 80, 80, 52, 82, 52, 50, 82, 82, 50, 26, 50, 19, 26, 83, 84, 27, 85, 86, 83, 12, 87, 85, 83, 86, 84, 86, 88, 84, 85, 87, 86, 87, 89, 86, 86, 89, 88, 89, 22, 88, 12, 11, 87, 11, 46, 87, 87, 46, 89, 46, 48, 89, 89, 48, 22, 48, 3, 22, 90, 91, 30, 92, 93, 90, 15, 94, 92, 90, 93, 91, 93, 95, 91, 92, 94, 93, 94, 96, 93, 93, 96, 95, 96, 23, 95, 15, 14, 94, 14, 61, 94, 94, 61, 96, 61, 63, 96, 96, 63, 23, 63, 10, 23, 97, 98, 33, 99, 100, 97, 18, 101, 99, 97, 100, 98, 100, 102, 98, 99, 101, 100, 101, 103, 100, 100, 103, 102, 103, 24, 102, 18, 17, 101, 17, 68, 101, 101, 68, 103, 68, 70, 103, 103, 70, 24, 70, 13, 24, 104, 105, 36, 106, 107, 104, 21, 108, 106, 104, 107, 105, 107, 109, 105, 106, 108, 107, 108, 110, 107, 107, 110, 109, 110, 25, 109, 21, 20, 108, 20, 73, 108, 108, 73, 110, 73, 75, 110, 110, 75, 25, 75, 16, 25, 84, 28, 27, 88, 111, 84, 22, 112, 88, 84, 111, 28, 111, 113, 28, 88, 112, 111, 112, 114, 111, 111, 114, 113, 114, 115, 113, 22, 9, 112, 9, 78, 112, 112, 78, 114, 78, 76, 114, 114, 76, 115, 76, 39, 115, 91, 31, 30, 95, 116, 91, 23, 117, 95, 91, 116, 31, 116, 118, 31, 95, 117, 116, 117, 119, 116, 116, 119, 118, 119, 120, 118, 23, 12, 117, 12, 85, 117, 117, 85, 119, 85, 83, 119, 119, 83, 120, 83, 27, 120, 98, 34, 33, 102, 121, 98, 24, 122, 102, 98, 121, 34, 121, 123, 34, 102, 122, 121, 122, 124, 121, 121, 124, 123, 124, 125, 123, 24, 15, 122, 15, 92, 122, 122, 92, 124, 92, 90, 124, 124, 90, 125, 90, 30, 125, 105, 37, 36, 109, 126, 105, 25, 127, 109, 105, 126, 37, 126, 128, 37, 109, 127, 126, 127, 129, 126, 126, 129, 128, 129, 130, 128, 25, 18, 127, 18, 99, 127, 127, 99, 129, 99, 97, 129, 129, 97, 130, 97, 33, 130, 77, 40, 39, 81, 131, 77, 26, 132, 81, 77, 131, 40, 131, 133, 40, 81, 132, 131, 132, 134, 131, 131, 134, 133, 134, 135, 133, 26, 21, 132, 21, 106, 132, 132, 106, 134, 106, 104, 134, 134, 104, 135, 104, 36, 135, 136, 137, 138, 139, 140, 136, 29, 141, 139, 136, 140, 137, 140, 142, 137, 139, 141, 140, 141, 143, 140, 140, 143, 142, 143, 41, 142, 29, 28, 141, 28, 113, 141, 141, 113, 143, 113, 115, 143, 143, 115, 41, 115, 39, 41, 144, 136, 138, 145, 146, 144, 32, 147, 145, 144, 146, 136, 146, 139, 136, 145, 147, 146, 147, 148, 146, 146, 148, 139, 148, 29, 139, 32, 31, 147, 31, 118, 147, 147, 118, 148, 118, 120, 148, 148, 120, 29, 120, 27, 29, 149, 144, 138, 150, 151, 149, 35, 152, 150, 149, 151, 144, 151, 145, 144, 150, 152, 151, 152, 153, 151, 151, 153, 145, 153, 32, 145, 35, 34, 152, 34, 123, 152, 152, 123, 153, 123, 125, 153, 153, 125, 32, 125, 30, 32, 154, 149, 138, 155, 156, 154, 38, 157, 155, 154, 156, 149, 156, 150, 149, 155, 157, 156, 157, 158, 156, 156, 158, 150, 158, 35, 150, 38, 37, 157, 37, 128, 157, 157, 128, 158, 128, 130, 158, 158, 130, 35, 130, 33, 35, 137, 154, 138, 142, 159, 137, 41, 160, 142, 137, 159, 154, 159, 155, 154, 142, 160, 159, 160, 161, 159, 159, 161, 155, 161, 38, 155, 41, 40, 160, 40, 133, 160, 160, 133, 161, 133, 135, 161, 161, 135, 38, 135, 36, 38 };
	Mesh* sphereMesh = new Mesh(sphereVerts, sphereIndices, 162, 960);
	m_meshes["sphere"] = sphereMesh;

	Material* greenMaterial = new Material();
	greenMaterial->m_diffuseColor = glm::vec4(0, 1, 0, 1);
	m_materials["green"] = greenMaterial;

	Material* redMaterial = new Material();
	redMaterial->m_diffuseColor = glm::vec4(1, 0, 0, 1);
	m_materials["red"] = redMaterial;

	Material* blueMaterial = new Material();
	blueMaterial->m_diffuseColor = glm::vec4(0, 0, 1, 1);
	m_materials["blue"] = blueMaterial;

	Material* yellowMaterial = new Material();
	yellowMaterial->m_diffuseColor = glm::vec4(1, 1, 0, 1);
	m_materials["yellow"] = yellowMaterial;

	Material* pinkMaterial = new Material();
	pinkMaterial->m_diffuseColor = glm::vec4(1.0, 0.34f, 0.6f, 1);
	m_materials["pink"] = pinkMaterial;

	// Enemey materials
	Material* enemyGreenMaterial = new Material();
	enemyGreenMaterial->m_diffuseColor = glm::vec4(0, 1, 0, 1);
	enemyGreenMaterial->m_noiseStrength = 0.15f;
	m_materials["enemy_green"] = enemyGreenMaterial;

	Material* enemyRedMaterial = new Material();
	enemyRedMaterial->m_diffuseColor = glm::vec4(1, 0, 0, 1);
	enemyRedMaterial->m_noiseStrength = 0.15f;
	m_materials["enemy_red"] = enemyRedMaterial;

	Material* enemyBlueMaterial = new Material();
	enemyBlueMaterial->m_diffuseColor = glm::vec4(0, 0, 1, 1);
	enemyBlueMaterial->m_noiseStrength = 0.15f;
	m_materials["enemy_blue"] = enemyBlueMaterial;

	Material* enemyYellowMaterial = new Material();
	enemyYellowMaterial->m_diffuseColor = glm::vec4(1, 1, 0, 1);
	enemyYellowMaterial->m_noiseStrength = 0.15f;
	m_materials["enemy_yellow"] = enemyYellowMaterial;

    m_shaderHeader = Utils::loadFile("data/shaders/globals");
}

DataManager::~DataManager()
{
	for (auto& texture : m_textures)
	{
		glDeleteTextures(1, &texture.second);
	}

	m_textures.clear();

	for (auto& material : m_materials)
	{
		delete material.second;
	}

	m_materials.clear();

	for (auto& mesh : m_meshes)
	{
		delete mesh.second;
	}

	m_meshes.clear();
}

GLuint DataManager::loadTexture(void* data, const glm::uvec2& dimensions, const std::string& name)
{
    // Return if it was loaded already
    auto foundTexture = m_textures.find(name);
    if (foundTexture != m_textures.end())
        return foundTexture->second;

    // Create texture, set OpenGL params
    GLuint texture;
    glActiveTexture(GL_TEXTURE0 + ShaderCommon::NON_USED_TEXTURE_BINDING);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    Globals::m_renderManager->setTextureParams(GL_TEXTURE_2D, GL_REPEAT, GL_LINEAR, GL_LINEAR, 1);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, dimensions.x, dimensions.y, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGB8, dimensions.x, dimensions.y);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, dimensions.x, dimensions.y, GL_RGB, GL_UNSIGNED_BYTE, data);

    m_textures[name] = texture;
    return texture;
}

GLuint DataManager::getTexture(const std::string& name)
{
    auto foundTexture = m_textures.find(name);
    if (foundTexture != m_textures.end())
        return foundTexture->second;
    else
        return 0;
}

Material* DataManager::getMaterial(const std::string& name)
{
    auto foundMaterial = m_materials.find(name);
    if (foundMaterial != m_materials.end())
        return foundMaterial->second;
    else
        return 0;
}

Material* DataManager::getMaterial(COLOR color)
{
	if (color == COLOR::STATIC)	return getMaterial("red");
	else if (color == COLOR::RED) return getMaterial("red");
	else if (color == COLOR::BLUE) return getMaterial("blue");
	else if (color == COLOR::GREEN) return getMaterial("green");
	else if (color == COLOR::YELLOW) return getMaterial("yellow");
	else return getMaterial("red");
}

Material* DataManager::getEnemyMaterial(COLOR color)
{
	// Copy the material
	if (color == COLOR::STATIC)	return new Material(*getMaterial("enemy_red"));
	else if (color == COLOR::RED) return new Material(*getMaterial("enemy_red"));
	else if (color == COLOR::BLUE) return new Material(*getMaterial("enemy_blue"));
	else if (color == COLOR::GREEN) return new Material(*getMaterial("enemy_green"));
	else if (color == COLOR::YELLOW) return new Material(*getMaterial("enemy_yellow"));
	else return new Material(*getMaterial("enemy_red"));
}

Mesh* DataManager::getMesh(const std::string& name)
{
    auto foundMesh = m_meshes.find(name);
    if (foundMesh != m_meshes.end())
        return foundMesh->second;
    else
        return 0;
}


GLuint DataManager::loadShaderProgram(const std::string& vertexShader, const std::string& fragmentShader)
{
    GLuint vertexShaderObject = createShader(GL_VERTEX_SHADER, vertexShader);
    GLuint fragmentShaderObject = createShader(GL_FRAGMENT_SHADER, fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShaderObject);
    glAttachShader(shaderProgram, fragmentShaderObject);
    glDeleteShader(vertexShaderObject);
    glDeleteShader(fragmentShaderObject);

    glLinkProgram(shaderProgram);
    checkProgram(shaderProgram);

    return shaderProgram;
}

GLuint DataManager::createShader(GLenum Type, const std::string& filename)
{
    std::string shaderSource = m_shaderHeader + Utils::loadFile(filename);
    const char* shaderSourceC = shaderSource.c_str();
    GLuint shader = glCreateShader(Type);
    glShaderSource(shader, 1, &shaderSourceC, 0);
    glCompileShader(shader);
    checkShader(shader);
    return shader;
}

bool DataManager::checkProgram(GLuint ProgramName)
{
    if (!ProgramName)
        return false;

    GLint Result = GL_FALSE;
    glGetProgramiv(ProgramName, GL_LINK_STATUS, &Result);

    int InfoLogLength;
    glGetProgramiv(ProgramName, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0)
    {
        std::vector<char> Buffer(glm::max(InfoLogLength, int(1)));
        glGetProgramInfoLog(ProgramName, InfoLogLength, NULL, &Buffer[0]);
        fprintf(stdout, "%s\n", &Buffer[0]);
    }

    return Result == GL_TRUE;
}

bool DataManager::checkShader(GLuint ShaderName)
{
    if (!ShaderName)
        return false;

    GLint Result = GL_FALSE;
    glGetShaderiv(ShaderName, GL_COMPILE_STATUS, &Result);

    int InfoLogLength;
    glGetShaderiv(ShaderName, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0)
    {
        std::vector<char> Buffer(InfoLogLength);
        glGetShaderInfoLog(ShaderName, InfoLogLength, NULL, &Buffer[0]);
        fprintf(stdout, "%s\n", &Buffer[0]);
    }

    return Result == GL_TRUE;
}
