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
	Mesh* cubeMesh = new Mesh(vertices, indices, 24, 36, { 0 });
    m_meshes["cube"] = cubeMesh;

	float sphereVerts[912] = { -0.191342f, -0.46194f, 0.0f, -0.403089f, -0.915159f, 0.0f, 0.0f, 1.0f, -0.353554f, -0.353553f, 0.0f, -0.718833f, -0.695151f, 0.0f, 0.0f, 1.0f, -0.326641f, -0.353553f, -0.135299f, -0.664113f, -0.695151f, -0.275094f, 0.0f, 1.0f, -0.46194f, -0.191342f, 0.0f, -0.927274f, -0.37434f, 0.0f, 0.0f, 1.0f, -0.426777f, -0.191342f, -0.176777f, -0.856685f, -0.37434f, -0.354839f, 0.0f, 1.0f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, -0.46194f, 0.0f, -0.191342f, -0.923856f, 0.0f, -0.382672f, 0.0f, 1.0f, -0.46194f, 0.191342f, 0.0f, -0.927274f, 0.37434f, 0.0f, 0.0f, 1.0f, -0.426777f, 0.191342f, -0.176777f, -0.856685f, 0.37434f, -0.354839f, 0.0f, 1.0f, -0.353554f, 0.353553f, 0.0f, -0.718833f, 0.695151f, 0.0f, 0.0f, 1.0f, -0.326641f, 0.353553f, -0.135299f, -0.664113f, 0.695151f, -0.275094f, 0.0f, 1.0f, -0.191342f, 0.46194f, 0.0f, -0.403089f, 0.915159f, 0.0f, 0.0f, 1.0f, -0.176777f, 0.46194f, -0.0732233f, -0.372387f, 0.915159f, -0.154241f, 0.0f, 1.0f, -0.176777f, -0.46194f, -0.0732233f, -0.372387f, -0.915159f, -0.154241f, 0.0f, 1.0f, -0.25f, -0.353553f, -0.25f, -0.508286f, -0.695151f, -0.508286f, 0.0f, 1.0f, -0.326641f, -0.191342f, -0.326641f, -0.65566f, -0.37434f, -0.65566f, 0.0f, 1.0f, -0.353554f, 0.0f, -0.353553f, -0.707083f, 0.0f, -0.707083f, 0.0f, 1.0f, -0.326641f, 0.191342f, -0.326641f, -0.65566f, 0.37434f, -0.65566f, 0.0f, 1.0f, -0.25f, 0.353553f, -0.25f, -0.508286f, 0.695151f, -0.508286f, 0.0f, 1.0f, -0.135299f, 0.46194f, -0.135299f, -0.285012f, 0.915159f, -0.285012f, 0.0f, 1.0f, -0.135299f, -0.46194f, -0.135299f, -0.285012f, -0.915159f, -0.285012f, 0.0f, 1.0f, -0.135299f, -0.353553f, -0.326641f, -0.275094f, -0.695151f, -0.664113f, 0.0f, 1.0f, -0.176777f, -0.191342f, -0.426777f, -0.354839f, -0.37434f, -0.856685f, 0.0f, 1.0f, -0.191342f, 0.0f, -0.46194f, -0.382672f, 0.0f, -0.923856f, 0.0f, 1.0f, -0.176777f, 0.191342f, -0.426777f, -0.354839f, 0.37434f, -0.856685f, 0.0f, 1.0f, -0.135299f, 0.353553f, -0.326641f, -0.275094f, 0.695151f, -0.664113f, 0.0f, 1.0f, -0.0732235f, 0.46194f, -0.176777f, -0.154241f, 0.915159f, -0.372387f, 0.0f, 1.0f, -0.0732234f, -0.46194f, -0.176777f, -0.154241f, -0.915159f, -0.372387f, 0.0f, 1.0f, -1.54497e-007f, -0.353553f, -0.353553f, 0.0f, -0.695151f, -0.718833f, 0.0f, 1.0f, -1.24695e-007f, -0.191342f, -0.46194f, 0.0f, -0.37434f, -0.927274f, 0.0f, 1.0f, -1.24695e-007f, 0.0f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, -1.24695e-007f, 0.191342f, -0.46194f, 0.0f, 0.37434f, -0.927274f, 0.0f, 1.0f, -1.54497e-007f, 0.353553f, -0.353553f, 0.0f, 0.695151f, -0.718833f, 0.0f, 1.0f, -1.84299e-007f, 0.46194f, -0.191342f, 0.0f, 0.915159f, -0.403089f, 0.0f, 1.0f, -1.47047e-007f, -0.46194f, -0.191342f, 0.0f, -0.915159f, -0.403089f, 0.0f, 1.0f, 0.135299f, -0.353553f, -0.326641f, 0.275094f, -0.695151f, -0.664113f, 0.0f, 1.0f, 0.176776f, -0.191342f, -0.426776f, 0.354839f, -0.37434f, -0.856685f, 0.0f, 1.0f, 0.191342f, 0.0f, -0.46194f, 0.382672f, 0.0f, -0.923856f, 0.0f, 1.0f, 0.176776f, 0.191342f, -0.426776f, 0.354839f, 0.37434f, -0.856685f, 0.0f, 1.0f, 0.135299f, 0.353553f, -0.326641f, 0.275094f, 0.695151f, -0.664113f, 0.0f, 1.0f, 0.073223f, 0.46194f, -0.176777f, 0.154241f, 0.915159f, -0.372387f, 0.0f, 1.0f, 0.0732231f, -0.46194f, -0.176777f, 0.154241f, -0.915159f, -0.372387f, 0.0f, 1.0f, 0.25f, -0.353553f, -0.25f, 0.508286f, -0.695151f, -0.508286f, 0.0f, 1.0f, 0.326641f, -0.191342f, -0.326641f, 0.65566f, -0.37434f, -0.65566f, 0.0f, 1.0f, 0.353553f, 0.0f, -0.353553f, 0.707083f, 0.0f, -0.707083f, 0.0f, 1.0f, 0.326641f, 0.191342f, -0.326641f, 0.65566f, 0.37434f, -0.65566f, 0.0f, 1.0f, 0.25f, 0.353553f, -0.25f, 0.508286f, 0.695151f, -0.508286f, 0.0f, 1.0f, 0.135299f, 0.46194f, -0.135299f, 0.285012f, 0.915159f, -0.285012f, 0.0f, 1.0f, 0.135299f, -0.46194f, -0.135299f, 0.285012f, -0.915159f, -0.285012f, 0.0f, 1.0f, 0.32664f, -0.353553f, -0.135299f, 0.664113f, -0.695151f, -0.275094f, 0.0f, 1.0f, 0.426776f, -0.191342f, -0.176776f, 0.856685f, -0.37434f, -0.354839f, 0.0f, 1.0f, 0.46194f, 0.0f, -0.191342f, 0.923856f, 0.0f, -0.382672f, 0.0f, 1.0f, 0.426776f, 0.191342f, -0.176776f, 0.856685f, 0.37434f, -0.354839f, 0.0f, 1.0f, 0.32664f, 0.353553f, -0.135299f, 0.664113f, 0.695151f, -0.275094f, 0.0f, 1.0f, 0.176776f, 0.46194f, -0.0732232f, 0.372387f, 0.915159f, -0.154241f, 0.0f, 1.0f, 0.176776f, -0.46194f, -0.0732232f, 0.372387f, -0.915159f, -0.154241f, 0.0f, 1.0f, 0.353553f, -0.353553f, 1.33331e-007f, 0.718833f, -0.695151f, 0.0f, 0.0f, 1.0f, 0.46194f, -0.191342f, 1.48232e-007f, 0.927274f, -0.37434f, 0.0f, 0.0f, 1.0f, 0.5f, 0.0f, 1.63133e-007f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.46194f, 0.191342f, 1.48232e-007f, 0.927274f, 0.37434f, 0.0f, 0.0f, 1.0f, 0.353553f, 0.353553f, 1.33331e-007f, 0.718833f, 0.695151f, 0.0f, 0.0f, 1.0f, 0.191341f, 0.46194f, 0.0f, 0.403089f, 0.915159f, 0.0f, 0.0f, 1.0f, 0.191341f, -0.46194f, 0.0f, 0.403089f, -0.915159f, 0.0f, 0.0f, 1.0f, 0.32664f, -0.353553f, 0.135299f, 0.664113f, -0.695151f, 0.275094f, 0.0f, 1.0f, 0.426776f, -0.191342f, 0.176777f, 0.856685f, -0.37434f, 0.354839f, 0.0f, 1.0f, 0.461939f, 0.0f, 0.191342f, 0.923856f, 0.0f, 0.382672f, 0.0f, 1.0f, 0.426776f, 0.191342f, 0.176777f, 0.856685f, 0.37434f, 0.354839f, 0.0f, 1.0f, 0.32664f, 0.353553f, 0.135299f, 0.664113f, 0.695151f, 0.275094f, 0.0f, 1.0f, 0.176776f, 0.46194f, 0.0732233f, 0.372387f, 0.915159f, 0.154241f, 0.0f, 1.0f, 0.176776f, -0.46194f, 0.0732234f, 0.372387f, -0.915159f, 0.154241f, 0.0f, 1.0f, 0.249999f, -0.353553f, 0.25f, 0.508286f, -0.695151f, 0.508286f, 0.0f, 1.0f, 0.32664f, -0.191342f, 0.326641f, 0.65566f, -0.37434f, 0.65566f, 0.0f, 1.0f, 0.353553f, 0.0f, 0.353553f, 0.707083f, 0.0f, 0.707083f, 0.0f, 1.0f, 0.32664f, 0.191342f, 0.326641f, 0.65566f, 0.37434f, 0.65566f, 0.0f, 1.0f, 0.249999f, 0.353553f, 0.25f, 0.508286f, 0.695151f, 0.508286f, 0.0f, 1.0f, 0.135299f, 0.46194f, 0.135299f, 0.285012f, 0.915159f, 0.285012f, 0.0f, 1.0f, 0.135299f, -0.46194f, 0.135299f, 0.285012f, -0.915159f, 0.285012f, 0.0f, 1.0f, 0.135299f, -0.353553f, 0.326641f, 0.275094f, -0.695151f, 0.664113f, 0.0f, 1.0f, 0.176776f, -0.191342f, 0.426777f, 0.354839f, -0.37434f, 0.856685f, 0.0f, 1.0f, 0.191341f, 0.0f, 0.46194f, 0.382672f, 0.0f, 0.923856f, 0.0f, 1.0f, 0.176776f, 0.191342f, 0.426777f, 0.354839f, 0.37434f, 0.856685f, 0.0f, 1.0f, 0.135299f, 0.353553f, 0.326641f, 0.275094f, 0.695151f, 0.664113f, 0.0f, 1.0f, 0.073223f, 0.46194f, 0.176777f, 0.154241f, 0.915159f, 0.372387f, 0.0f, 1.0f, 0.073223f, -0.46194f, 0.176777f, 0.154241f, -0.915159f, 0.372387f, 0.0f, 1.0f, -3.63113e-007f, -0.353553f, 0.353553f, 0.0f, -0.695151f, 0.718833f, 0.0f, 1.0f, -3.78015e-007f, -0.191342f, 0.46194f, 0.0f, -0.37434f, 0.927274f, 0.0f, 1.0f, -4.22718e-007f, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, -3.78015e-007f, 0.191342f, 0.46194f, 0.0f, 0.37434f, 0.927274f, 0.0f, 1.0f, -3.63113e-007f, 0.353553f, 0.353553f, 0.0f, 0.695151f, 0.718833f, 0.0f, 1.0f, -2.43904e-007f, 0.46194f, 0.191342f, 0.0f, 0.915159f, 0.403089f, 0.0f, 1.0f, -2.88608e-007f, -0.46194f, 0.191342f, 0.0f, -0.915159f, 0.403089f, 0.0f, 1.0f, -0.135299f, -0.353553f, 0.32664f, -0.275094f, -0.695151f, 0.664113f, 0.0f, 1.0f, -0.176777f, -0.191342f, 0.426776f, -0.354839f, -0.37434f, 0.856685f, 0.0f, 1.0f, -0.191342f, 0.0f, 0.46194f, -0.382672f, 0.0f, 0.923856f, 0.0f, 1.0f, -0.176777f, 0.191342f, 0.426776f, -0.354839f, 0.37434f, 0.856685f, 0.0f, 1.0f, -0.135299f, 0.353553f, 0.32664f, -0.275094f, 0.695151f, 0.664113f, 0.0f, 1.0f, -0.0732235f, 0.46194f, 0.176776f, -0.154241f, 0.915159f, 0.372387f, 0.0f, 1.0f, -0.0732235f, -0.46194f, 0.176776f, -0.154241f, -0.915159f, 0.372387f, 0.0f, 1.0f, -0.25f, -0.353553f, 0.25f, -0.508286f, -0.695151f, 0.508286f, 0.0f, 1.0f, -0.326641f, -0.191342f, 0.32664f, -0.65566f, -0.37434f, 0.65566f, 0.0f, 1.0f, -0.353554f, 0.0f, 0.353553f, -0.707083f, 0.0f, 0.707083f, 0.0f, 1.0f, -0.326641f, 0.191342f, 0.32664f, -0.65566f, 0.37434f, 0.65566f, 0.0f, 1.0f, -0.25f, 0.353553f, 0.25f, -0.508286f, 0.695151f, 0.508286f, 0.0f, 1.0f, -0.135299f, 0.46194f, 0.135299f, -0.285012f, 0.915159f, 0.285012f, 0.0f, 1.0f, -0.135299f, -0.46194f, 0.135299f, -0.285012f, -0.915159f, 0.285012f, 0.0f, 1.0f, -0.326641f, -0.353553f, 0.135299f, -0.664113f, -0.695151f, 0.275094f, 0.0f, 1.0f, -0.426777f, -0.191342f, 0.176776f, -0.856685f, -0.37434f, 0.354839f, 0.0f, 1.0f, -0.46194f, 0.0f, 0.191341f, -0.923856f, 0.0f, 0.382672f, 0.0f, 1.0f, -0.426777f, 0.191342f, 0.176776f, -0.856685f, 0.37434f, 0.354839f, 0.0f, 1.0f, -0.326641f, 0.353553f, 0.135299f, -0.664113f, 0.695151f, 0.275094f, 0.0f, 1.0f, -0.176777f, 0.46194f, 0.0732232f, -0.372387f, 0.915159f, 0.154241f, 0.0f, 1.0f, -1.94446e-007f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, -2.47831e-007f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, -0.176777f, -0.46194f, 0.0732232f, -0.372387f, -0.915159f, 0.154241f, 0.0f, 1.0f };
	ushort sphereIndices[672] = { 0, 1, 2, 1, 3, 4, 3, 5, 6, 5, 7, 8, 7, 9, 10, 9, 11, 12, 13, 2, 14, 2, 4, 15, 4, 6, 16, 6, 8, 17, 10, 18, 17, 12, 19, 18, 20, 14, 21, 14, 15, 22, 15, 16, 23, 16, 17, 24, 17, 18, 25, 18, 19, 26, 27, 21, 28, 22, 29, 28, 22, 23, 30, 24, 31, 30, 24, 25, 32, 25, 26, 33, 34, 28, 35, 28, 29, 36, 29, 30, 37, 31, 38, 37, 31, 32, 39, 32, 33, 40, 41, 35, 42, 35, 36, 43, 36, 37, 44, 37, 38, 45, 38, 39, 46, 39, 40, 47, 48, 42, 49, 42, 43, 50, 43, 44, 51, 44, 45, 52, 46, 53, 52, 46, 47, 54, 55, 49, 56, 49, 50, 57, 50, 51, 58, 51, 52, 59, 53, 60, 59, 53, 54, 61, 62, 56, 63, 56, 57, 64, 57, 58, 65, 58, 59, 66, 60, 67, 66, 60, 61, 68, 69, 63, 70, 63, 64, 71, 64, 65, 72, 65, 66, 73, 67, 74, 73, 67, 68, 75, 76, 70, 77, 70, 71, 78, 71, 72, 79, 72, 73, 80, 74, 81, 80, 74, 75, 82, 83, 77, 84, 77, 78, 85, 79, 86, 85, 79, 80, 87, 81, 88, 87, 81, 82, 89, 90, 84, 91, 84, 85, 92, 86, 93, 92, 86, 87, 94, 88, 95, 94, 88, 89, 96, 97, 91, 98, 91, 92, 99, 93, 100, 99, 93, 94, 101, 95, 102, 101, 95, 96, 103, 104, 98, 105, 98, 99, 106, 100, 107, 106, 100, 101, 108, 102, 109, 108, 102, 103, 110, 111, 0, 13, 11, 112, 12, 111, 13, 20, 12, 112, 19, 111, 20, 27, 19, 112, 26, 111, 27, 34, 26, 112, 33, 111, 34, 41, 33, 112, 40, 111, 41, 48, 40, 112, 47, 111, 48, 55, 47, 112, 54, 111, 55, 62, 54, 112, 61, 111, 62, 69, 61, 112, 68, 111, 69, 76, 68, 112, 75, 111, 76, 83, 75, 112, 82, 111, 83, 90, 82, 112, 89, 111, 90, 97, 89, 112, 96, 111, 97, 104, 96, 112, 103, 111, 104, 113, 103, 112, 110, 111, 113, 0, 105, 1, 0, 106, 3, 1, 107, 5, 3, 107, 108, 7, 108, 109, 9, 109, 110, 11, 110, 112, 11, 13, 0, 2, 2, 1, 4, 4, 3, 6, 6, 5, 8, 8, 7, 10, 10, 9, 12, 20, 13, 14, 14, 2, 15, 15, 4, 16, 16, 6, 17, 8, 10, 17, 10, 12, 18, 27, 20, 21, 21, 14, 22, 22, 15, 23, 23, 16, 24, 24, 17, 25, 25, 18, 26, 34, 27, 28, 21, 22, 28, 29, 22, 30, 23, 24, 30, 31, 24, 32, 32, 25, 33, 41, 34, 35, 35, 28, 36, 36, 29, 37, 30, 31, 37, 38, 31, 39, 39, 32, 40, 48, 41, 42, 42, 35, 43, 43, 36, 44, 44, 37, 45, 45, 38, 46, 46, 39, 47, 55, 48, 49, 49, 42, 50, 50, 43, 51, 51, 44, 52, 45, 46, 52, 53, 46, 54, 62, 55, 56, 56, 49, 57, 57, 50, 58, 58, 51, 59, 52, 53, 59, 60, 53, 61, 69, 62, 63, 63, 56, 64, 64, 57, 65, 65, 58, 66, 59, 60, 66, 67, 60, 68, 76, 69, 70, 70, 63, 71, 71, 64, 72, 72, 65, 73, 66, 67, 73, 74, 67, 75, 83, 76, 77, 77, 70, 78, 78, 71, 79, 79, 72, 80, 73, 74, 80, 81, 74, 82, 90, 83, 84, 84, 77, 85, 78, 79, 85, 86, 79, 87, 80, 81, 87, 88, 81, 89, 97, 90, 91, 91, 84, 92, 85, 86, 92, 93, 86, 94, 87, 88, 94, 95, 88, 96, 104, 97, 98, 98, 91, 99, 92, 93, 99, 100, 93, 101, 94, 95, 101, 102, 95, 103, 113, 104, 105, 105, 98, 106, 99, 100, 106, 107, 100, 108, 101, 102, 108, 109, 102, 110, 113, 105, 0, 105, 106, 1, 106, 107, 3, 5, 107, 7, 7, 108, 9, 9, 109, 11 };
	Mesh* sphereMesh = new Mesh(sphereVerts, sphereIndices, 114, 672, { 0 });
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
    auto& foundTexture = m_textures.find(name);
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
    auto& foundTexture = m_textures.find(name);
    if (foundTexture != m_textures.end())
        return foundTexture->second;
    else
        return 0;
}

Material* DataManager::getMaterial(const std::string& name)
{
    auto& foundMaterial = m_materials.find(name);
    if (foundMaterial != m_materials.end())
        return foundMaterial->second;
    else
        return 0;
}

Mesh* DataManager::getMesh(const std::string& name)
{
    auto& foundMesh = m_meshes.find(name);
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
