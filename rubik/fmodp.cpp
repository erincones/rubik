#include "fmodp.h"

fmodp::fmodp()
{
	init();
}


fmodp::~fmodp()
{
	for (int i = 0; i < sonidos.size(); i++) {
		FMOD_RESULT result;
		result = sonidos[i].sonido->release();
	}
	audio->close();
	audio->release();
}

bool fmodp::init() {
	{
		FMOD_RESULT result;
		result = FMOD::System_Create(&audio);
		if (result != FMOD_OK)
		{
			return false;
		}
		result = audio->init(50, FMOD_INIT_NORMAL, NULL);
		if (result != FMOD_OK)
		{
			return false;
		}
		return true;
	}
}

const bool fmodp::loadsound(std::string cancion,const std::string path,float volum){
	sn aux;
	FMOD::Sound* sonido;
	FMOD_RESULT result;
	result = audio->createSound(path.c_str(), FMOD_DEFAULT, 0, &sonido);
	aux.sonido = sonido;
	aux.nombre = cancion;
	aux.volume = volum;
	sonidos.push_back(aux);
	return true;
}

const bool fmodp::loadch(std::string nombrep,std::string modo){
	FMOD::Channel* auxch;
	FMOD_RESULT result;
	int aux=NULL;
	for(int i=0;i<sonidos.size();i++){
		if (nombrep==sonidos[i].nombre) {
			if (sonidos[i].indicech == NULL) {
				canales.push_back(auxch);
				sonidos[i].indicech = canales.size()-1;
			}
			if (modo == "loop") {
				result = sonidos[i].sonido->setMode(FMOD_LOOP_NORMAL);
				result = audio->playSound(sonidos[i].sonido, 0,true, &canales[sonidos[i].indicech]);
			}
			if (modo == "stream") {
				result = audio->playSound(sonidos[i].sonido, 0,true, &canales[sonidos[i].indicech]);
			}
			break;
		}
	}
	return true;
}

const bool fmodp::loopplay(std::string nombrep) {
	FMOD::Channel* auxch;
	FMOD_RESULT result;
	bool paused=0;
	int aux = NULL;
	for (int i = 0; i<sonidos.size(); i++) {
		if (nombrep == sonidos[i].nombre) {
			result = canales[sonidos[i].indicech]->getPaused(&paused);
				if (paused) {
					canales[sonidos[i].indicech]->setVolume(sonidos[i].volume);
					canales[sonidos[i].indicech]->setPaused(false);
				}
				else {
					if (!paused) {
						canales[sonidos[i].indicech]->setPaused(true);
					}
				}
			
			break;
		}
	}
	std::cout << sonidos.size() << std::endl;
	return true;
}

const bool fmodp::playsound(std::string nombrec) {
	FMOD_RESULT result;
	for (int i = 0; i < sonidos.size(); i++) {
		if (nombrec == sonidos[i].nombre) {
			result = audio->playSound(sonidos[i].sonido, 0, false, &canales[sonidos[i].indicech]);
			canales[sonidos[i].indicech]->setPaused(true);
			canales[sonidos[i].indicech]->setVolume(sonidos[i].volume);
			canales[sonidos[i].indicech]->setPaused(false);
			break;
		}
	}
	return true;
}

const bool fmodp::altvol(std::string param,std::string nombre) {
	FMOD_RESULT result;
	float curvol = 0.0f,aux=0.0f;
	for (int i = 0; i < sonidos.size(); i++) {
		if (nombre == sonidos[i].nombre) {
			canales[sonidos[i].indicech]->setPaused(true);
			canales[sonidos[i].indicech]->getVolume(&curvol);
			std::cout << curvol << std::endl;
			if (param == "min") {
				if (curvol > 0.0f) {
					aux = curvol - 0.1f; 
				}
				if ((curvol - 0.1f)<0.0f) {
						aux = 0.0f;	
				}
				canales[sonidos[i].indicech]->setVolume(aux);
			}else{
				if (param == "max") {
					if (curvol < 1.0f) {
						aux = curvol+0.1f;
					}
					if ((curvol + 0.1f) > 1.0f){
						aux = 1.0f;
					}
					canales[sonidos[i].indicech]->setVolume(aux);
					std::cout << aux << std::endl;
				}
			}
			canales[sonidos[i].indicech]->setPaused(false);
			break;
		}
	}
	return true;
}

const bool fmodp::loadstream(std::string cancion, const std::string path, float volum) {
	sn aux;
	FMOD::Sound* sonido;
	FMOD_RESULT result;
	result = audio->createStream(path.c_str(), FMOD_LOOP_NORMAL | FMOD_2D, 0, &sonido);
	aux.sonido = sonido;
	aux.nombre = cancion;
	aux.volume = volum;
	sonidos.push_back(aux);
	return true;
};
const bool fmodp::playstream(std::string nombrec) {
	FMOD::Channel* auxch;
	FMOD_RESULT result;
	bool paused = 0;
	int aux = NULL;
	for (int i = 0; i<sonidos.size(); i++) {
		if (nombrec == sonidos[i].nombre) {
			result = canales[sonidos[i].indicech]->getPaused(&paused);
			if (paused) {
				//canales[sonidos[i].indicech]->setPaused(true);
				canales[sonidos[i].indicech]->setVolume(sonidos[i].volume);
				canales[sonidos[i].indicech]->setPaused(false);
			}
			else {
				if(!paused){
					canales[sonidos[i].indicech]->setPaused(true);
				}
			}

			break;
		}
	}
	std::cout << sonidos.size() << std::endl;
	return true;
};