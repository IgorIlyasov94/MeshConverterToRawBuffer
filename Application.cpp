#include "Application.h"

Application::Application()
{

}

Application::~Application()
{

}

int Application::Run()
{
	try
	{
		std::cout << "Select target mesh file:" << std::endl;

		std::string selectedFilePath;

		GetFilePathFromDialog(selectedFilePath);

		std::cout << selectedFilePath << std::endl << std::endl;
		
		std::filesystem::path meshFilePath(selectedFilePath);

		char calculateNormals{};

		std::cout << "Calculate normals? (Y - yes/N - no):" << std::endl;
		std::cin >> calculateNormals;
		std::cout << std::endl;

		char smoothNormals{};

		std::cout << "Smooth normals? (Y - yes/N - no):" << std::endl;
		std::cin >> smoothNormals;
		std::cout << std::endl;

		VertexFormat vertexFormat{};

		std::vector<uint8_t> vertexBuffer;
		std::vector<uint8_t> indexBuffer;

		OBJLoader::Load(meshFilePath, calculateNormals == 'Y' || calculateNormals == 'y', smoothNormals == 'Y' || smoothNormals == 'y', vertexFormat,
			vertexBuffer, indexBuffer);

		std::cout << "Loading done!" << std::endl << std::endl;
		
		std::string vertexBufferPath = meshFilePath.filename().string() + "_VertexBuffer.bin";
		
		OBJLoader::SaveVertexBuffer(vertexBufferPath, vertexBuffer);

		std::cout << "VertexBuffer saved:" << std::endl;

		std::cout << vertexBufferPath << std::endl;

		std::string indexBufferPath = meshFilePath.filename().string() + "_IndexBuffer.bin";

		OBJLoader::SaveVertexBuffer(indexBufferPath, indexBuffer);

		std::cout << "VertexBuffer saved:" << std::endl;

		std::cout << indexBufferPath << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}
