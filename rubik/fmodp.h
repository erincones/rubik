#ifndef FMODP_H
#define FMODP_H
#include <fmod\fmod.hpp>
#include <stdlib.h>
#include <vector>
#include <iostream>

struct sn {
	FMOD::Sound* sonido;
	std::string nombre;
	std::string tipo;
	float volume;
	int indicech=NULL;
};

class fmodp
{
private:
	FMOD::System* audio;
	std::vector<sn> sonidos;
	std::vector<FMOD::Channel*> canales;
public:
	fmodp();
	~fmodp();
	bool init();
	const bool loadsound(std::string cancion,const std::string path,float volum);
	const bool loadch(std::string nombrep,std::string modo);
	const bool loopplay(std::string nombrep);
	const bool playsound(std::string nombrep);
	const bool altvol(std::string param, std::string nombre);
	const bool loadstream(std::string cancion, const std::string path, float volum);
	const bool playstream(std::string nombrec);
};

#endif