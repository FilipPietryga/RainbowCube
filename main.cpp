#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <iostream>

int main() {

	//inicjalizacja glfw i sprawdzenie bledow
	if (!glfwInit()) {
		glfwTerminate();
		std::cerr << "Glfw Error";
		return -1;
	}

	//inicjalizacja glew i sprawdzenie bledow
	if (!glewInit()) {
		glfwTerminate();
		std::cerr << "Glew Error";
		return -2;
	}

	//tworzymy zmienna na obiekt okna
	GLFWwindow* window; 

	//tworzymy okno
	window = glfwCreateWindow(640, 480, "Okno Polsl", NULL, NULL); 

	//sprawdzamy czy okno zostalo poprawnie utworzone
	if (!window) {
		glfwTerminate();
		std::cerr << "Window Error";
		return -3;
	}

	//wiazemy maszyne stanow z oknem
	glfwMakeContextCurrent(window);

	//ustawiamy zmienne na stan poczatkowy
	//ow zmienne beda mialy wplyw na renderowanie obiektu
	float angle = 0.0f;
	float x = 0.0f, y = 0.0f, z = 0.0f;
	double r = 0.0, g = 0.0, b = 0.0;
	float cx = 0.0f, cy = 0.0f, cz = 0.0f;

	//zmiana skladowych kolorow
	double deltar = 0.0003;
	double deltag = 0.0005;
	double deltab = 0.0007;

	//stopien przeskalowania
	double scale = 1.0f;

	//zmiana translacji
	float deltax = 0.001f;
	float deltay = 0.003f;

	//przesuniecie obiektu
	float tx = 0.0f, ty = 0.0f, tz = 0.0f;

	//glowna petla programu
	while (!glfwWindowShouldClose(window)) {

		//czyscimy bufor 
		glClear(GL_COLOR_BUFFER_BIT);

		//ustawiamy tryb pracy z macierzami
		glMatrixMode(GL_MODELVIEW);

		//ustawiamy macierz jednostkowa
		glLoadIdentity();

		//kolejne przeksztalcania bryly
		glTranslated(tx, ty, tz);
		glRotatef(angle, x, y, z);
		glScalef(scale, scale, scale);

		//rysowanie prymitywow...
		//w tym przypadku linii
		glBegin(GL_LINE_STRIP);

		//ustawianie koloru
		glColor3d(r, g, b);

		//ustawienie poszczegolnych linii
		glVertex3f(-0.5 + cx, -0.5 + cy, 0.5 + cz);
		glVertex3f(0.5 + cx, -0.5 + cy, 0.5 + cz);
		glVertex3f(0.5 + cx, 0.5 + cy, 0.5 + cz);
		glVertex3f(-0.5 + cx, 0.5 + cy, 0.5 + cz);

		glVertex3f(-0.5 + cx, -0.5 + cy, 0.5 + cz);
		glVertex3f(-0.5 + cx, -0.5 + cy, -0.5 + cz);
		glVertex3f(0.5 + cx, -0.5 + cy, -0.5 + cz);
		glVertex3f(0.5 + cx, 0.5 + cy, -0.5 + cz);

		glVertex3f(-0.5 + cx, 0.5 + cy, -0.5 + cz);
		glVertex3f(-0.5 + cx, -0.5 + cy, -0.5 + cz);
		glVertex3f(-0.5 + cx, -0.5 + cy, -0.5 + cz);
		glVertex3f(0.5 + cx, -0.5 + cy, -0.5 + cz);

		glVertex3f(0.5 + cx, -0.5 + cy, 0.5 + cz);
		glVertex3f(-0.5 + cx, -0.5 + cy, 0.5 + cz);
		glVertex3f(-0.5 + cx, -0.5 + cy, -0.5 + cz);
		glVertex3f(-0.5 + cx, -0.5 + cy, -0.5 + cz);

		glVertex3f(-0.5 + cx, 0.5 + cy, -0.5 + cz);
		glVertex3f(-0.5 + cx, 0.5 + cy, 0.5 + cz);
		glVertex3f(-0.5 + cx, -0.5 + cy, 0.5 + cz);
		glVertex3f(-0.5 + cx, -0.5 + cy, -0.5 + cz);

		glVertex3f(-0.5 + cx, -0.5 + cy, 0.5 + cz);
		glVertex3f(0.5 + cx, -0.5 + cy, 0.5 + cz);
		glVertex3f(0.5 + cx, 0.5 + cy, 0.5 + cz);
		glVertex3f(0.5 + cx, 0.5 + cy, -0.5 + cz);
		
		glEnd();

		//oproznij macierz
		glPopMatrix();

		//pobieramy input z zewnatrz
		glfwPollEvents();

		//ustawiamy to co 'narysowalismy' na ekran
		glfwSwapBuffers(window);


		//zmieniamy kat obracania 
		//sie oraz oœ
		angle += 0.01f;
		x += 0.003f;
		y += 0.005f;
		z += 0.007f;

		//zmieniamy poszczegolne 
		//skladowe koloru
		r += deltar;
		g += deltag;
		b += deltab;

		//w przypadku przekroczenia pewnych granic
		//zmieniamy sposob naliczania skladowych kolorow
		(r > 1.0 || r < 0.0f) ? (deltar =- deltag) : r;
		(g > 1.0 || g < 0.0f) ? (deltag = -deltab) : g;
		(b > 1.0 || b < 0.0f) ? (deltab = -deltar) : b;

		//tx += deltax;
		//ty += deltay;
		//std::cout << "X:" << tx << "Y:" << ty << std::endl;

		//tx > 1.0f - 0.7f * scale || tx < -1.0f + 0.7f * scale ? deltax = -deltax : deltax;
		//ty > 1.0f - 0.7f * scale || ty < -1.0f + 0.7f * scale ? deltay = -deltay : deltay;


		//pod wplywem prawego klawisza
		//zwieksz obiekt
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
			scale *= 1.001f;
		}

		//pod wplywem lewego klawisza
		//zmniejsz obiekt
		else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
			scale /= 1.001f;
		}
	}

	//'odlacz biblioteke'
	glfwTerminate();
	return 0;
}