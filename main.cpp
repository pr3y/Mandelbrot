#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#define LOG(x) std::cout << x << std::endl;


int calcMandelbrot(double cr, double ci, int max_iterations) //funcao que calcula Mandelbrot
			               				//tem no wikipedia :P
{
    int i = 0;
    double zr = 0.0, zi = 0.0;
    while (i < max_iterations && zr * zr + zi * zi < 4.0)
    {
        double temp = zr * zr - zi * zi + cr;
        zi = 2.0 * zr * zi + ci;
        zr = temp;
        i++;
    }
    return i;

}

double mapToReal(int x,int imageWidth, double minR, double maxR) //funcao p/ calcular e atualizar valores 
{
    double range = maxR - minR;
    return x * (range / imageWidth) + minR;
}

double maptoImaginary(int y, int imageHeight, double minI, double maxI)
{
    double range = maxI - minI;
    return y * (range / imageHeight) + minI;
}


int main()
{
srand(time(NULL));  //seed para numero aleatorio (usa time.h)

int randR = rand() % 100; //cria variaveis com numeros aleatorios (para gerar mandelbrot colorido)
int randG = rand() % 100;
int randB = rand() % 100;  



    int color;			//menu
    LOG("----------------");
    LOG("Gerar Mandelbrot com:");
    LOG("1 - COR (aleatorio)\n2 - PRETO E BRANCO");
    LOG("----------------\n");

    std::cin >> color; //le opcao
    LOG("Gerando Imagem...");
    std::ifstream fin("base.txt"); //le arquivo base para configuracao 
                                    //para info de configuracao, va no help_base.txt
    int imageWidth, imageHeight, maxN; //cria variaveis que serao lidas no arquivo
    double minR, maxR, minI, maxI;
    if (!fin)
    {
        LOG("nao deu p abrir o arquivo");
	std::cin.ignore();
        return EXIT_FAILURE;
    }
    fin >> imageWidth >> imageHeight >> maxN;
    fin >> minR >> maxR >> minI >> maxI;

    std::ofstream fout("mandelbrot.ppm"); //arquivo imagem final gerado (.ppm)
    fout << "P3" << std::endl; //magic number do arquivo (indica ppm)
    fout << imageWidth << " " << imageHeight << std::endl; //resolucao
    fout << "256" << std::endl; //valor maximo do rgb

    for (int y=0;y<imageHeight;y++) //filas
    {
        for (int x=0; x<imageWidth;x++) // pixels nas colunas
        {
            double cr = mapToReal(x, imageWidth, minR, maxR); //calcula valor real e imaginario que 
            double ci = maptoImaginary(y, imageHeight, minI, maxI); //corresponde com o x,y na imagem

            int n= calcMandelbrot(cr, ci, maxN); //calcula numero de interações na funcao calcMandelbrot
		
	    if(color == 1){ //se for colorido 
            int r = (((n * randR)) % 256);
            int g = ((n * randG) % 256);
            int b = ((n * randB) % 256);

            fout << r << " " << g << " " << b << " "; //faz output da imagem
	   }
	    else if(color == 2){ //se for preto e branco
	    int r = (n % 256);
            int g = (n % 256);
            int b = (n % 256);

            fout << r << " " << g << " " << b << " ";	
    
	    }
	    else{ // opcao invalida
		 LOG("INSIRA UMA OPCAO VALIDA!");
	    	 return EXIT_FAILURE;
	    }


        }
        fout << std::endl;
    }
    fout.close();
    LOG("Finalizado! mandelbrot.ppm adicionado no diretorio atual");
    return EXIT_SUCCESS;
}
