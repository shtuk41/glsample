/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


GLuint initializeTexture(const unsigned char *image_data, int width, int height, GLenum format)
{
	GLuint textureID = 0;

	//create and bind one texture element
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);

	/* Specify target texture.  The parameters describe
	the format and type of the image data */

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, format, 
				GL_UNSIGNED_BYTE, image_data);

	/*Set the wrap parameter for texture coordinate s & t to GL_CLAMP, 
	which clamsp the coordinates within [0,1] */

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	/*Set  the magnification method to linear and return weighted 
	average of four texture elements closest to the center of 
	the pixel */

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	/*choose the mipmap that most closely matches the size of the 
	pixel being texture and use the GL_NEAREST criterion (the 
	texture element nearest to the center of the pixel) to 
	produce a texture value */

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	return textureID;
}

void updateTexture(const unsigned char *image_data, int width, int height, GLenum format)
{
	//Update Texture
	glTexSubImage2D (GL_TEXTURE_2D, 0,0,0, width, height, format, GL_UNSIGNED_BYTE, image_data);

	/*Sets the wrap parameter for texture coordinate s& t to GL_CLAMP, 
	which clamps the coordinates within [0,1] */

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	/*Set  the magnification method to linear and return weighted 
	average of four texture elements closest to the center of 
	the pixel */

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	/*choose the mipmap that most closely matches the size of the 
	pixel being texture and use the GL_NEAREST criterion (the 
	texture element nearest to the center of the pixel) to 
	produce a texture value */

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
}

GLuint loadImageToTexture(const char * imagePath)
{
	int width, height, channels;
	GLuint textureID = 0;
	//Load the images and convert them to RGBA format

        unsigned char *image = SOIL_load_image(imagePath, &width, &height, &channels, SOIL_LOAD_RGBA);

	if (!image)
	{
		std::cout << "Failed to load image " << imagePath << std::endl;
		return textureID;
	}

	std::cout << "Loaded Image: " << width << " x " << height << " - " << channels << " channels" << std::endl;
        textureID = initializeTexture(image, width, height, GL_RGBA);
	SOIL_free_image_data(image);
	return textureID;
}
