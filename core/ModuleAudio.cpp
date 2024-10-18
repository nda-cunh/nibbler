# include "ModuleAudio.hpp"

/* ____ CONSTRUCTORS ____ */
ModuleAudio::ModuleAudio() :
	audio(nullptr),
	handler(nullptr)
{
	handler = dlopen("./libaudio.so", RTLD_LAZY);
	if (handler == NULL)
		throw std::runtime_error("can't load libaudio.so");
	auto func = reinterpret_cast<IAudioModule*(*)()>(dlsym(handler, "load"));
	if (func == NULL)
		throw std::runtime_error("can't dlsym \"load\" function");
	audio = func();
};

ModuleAudio::~ModuleAudio() {
	auto func = reinterpret_cast<void(*)(IAudioModule*)>(dlsym(handler, "unload"));
	if (func != NULL)
		func(audio);
	if (dlclose(handler) != 0)
		std::cerr << "dlclose have an error" << std::endl;
}

/* ____ COPLIEN ____ */
ModuleAudio::ModuleAudio(const ModuleAudio &src):
	audio(src.audio),
	handler(src.handler)
{ }

ModuleAudio& ModuleAudio::operator=(const ModuleAudio &rhs){
	if (this == &rhs)
		return *this;
	audio = rhs.audio;
	handler = rhs.handler;
	return *this;
}

/* ____ METHODS ____ */
void ModuleAudio::playSound(const SoundType &soundType) {
	audio->playSound(soundType);
}
