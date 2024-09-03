# include "ModuleAudio.hpp"

/* ____ CONSTRUCTORS ____ */
ModuleAudio::ModuleAudio() {
	handler = dlopen("./libaudio.so", RTLD_LAZY);
	if (handler == NULL)
		throw std::runtime_error("can't load libaudio.so");
	auto func = (IAudioModule*(*)())dlsym(handler, "load");
	if (func == NULL)
		throw std::runtime_error("can't dlsym \"load\" function");
	audio = func();
};

ModuleAudio::~ModuleAudio() {
	auto func = (void(*)(IAudioModule*))dlsym(handler, "unload");
	if (func != NULL)
		func(audio);
	if (dlclose(handler) != 0)
		std::cerr << "dlclose have an error" << std::endl;
}

/* ____ COPLIEN ____ */
ModuleAudio::ModuleAudio(const ModuleAudio &src) {
	*this = src;
}

// TODO: implement operator= for ModuleAudio
ModuleAudio& ModuleAudio::operator=(const ModuleAudio &rhs){
	if (this == &rhs)
		return *this;
	return *this;
}


/* ____ METHODS ____ */
void ModuleAudio::playSound(const SoundType &soundType) {
	audio->playSound(soundType);
}
