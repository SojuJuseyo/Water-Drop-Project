#include "Sound.h"

namespace Moo
{
	Sound::Sound()
	{
		_currentState = false;
	}

	Sound::~Sound()
	{
		/*
		fclose(fp);
		delete[] buf;
		alDeleteSources(1, &_source);
		alDeleteBuffers(1, &buffer);
		*/
	}

	ALuint Sound::getSource()
	{
		return _source;
	}

	bool	Sound::loadSound(const std::string &filename)
	{
		FILE *fp = NULL;
		fopen_s(&fp, filename.c_str(), "rb");
		if (!fp) {
			std::cout << "open failed" << std::endl;
			return false;
		}
		char type[4];
		DWORD size, chunkSize;
		short formatType, channels;
		DWORD sampleRate, avgBytesPerSec;
		short bytesPerSample, bitsPerSample;
		DWORD dataSize;

		fread(type, sizeof(char), 4, fp);
		if (type[0] != 'R' || type[1] != 'I' || type[2] != 'F' || type[3] != 'F')
			return false;

		fread(&size, sizeof(DWORD), 1, fp);
		fread(type, sizeof(char), 4, fp);
		if (type[0] != 'W' || type[1] != 'A' || type[2] != 'V' || type[3] != 'E')
			return false;

		fread(type, sizeof(char), 4, fp);
		if (type[0] != 'f' || type[1] != 'm' || type[2] != 't' || type[3] != ' ')
			return false;

		fread(&chunkSize, sizeof(DWORD), 1, fp);
		fread(&formatType, sizeof(short), 1, fp);
		fread(&channels, sizeof(short), 1, fp);
		fread(&sampleRate, sizeof(DWORD), 1, fp);
		fread(&avgBytesPerSec, sizeof(DWORD), 1, fp);
		fread(&bytesPerSample, sizeof(short), 1, fp);
		fread(&bitsPerSample, sizeof(short), 1, fp);

		fread(type, sizeof(char), 4, fp);
		fread(&dataSize, sizeof(DWORD), 1, fp);
		
		unsigned char* buf = new unsigned char[dataSize];
		fread(buf, sizeof(BYTE), dataSize, fp);

		ALuint buffer;
		ALuint frequency = sampleRate;
		ALenum format = 0;

		alGenBuffers(1, &buffer);
		alGenSources(1, &_source);
		if (alGetError() != AL_NO_ERROR) {
			std::cout << "alerror" << std::endl;
			return false;
		}

		if (bitsPerSample == 8)
		{
			if (channels == 1)
				format = AL_FORMAT_MONO8;
			else if (channels == 2)
				format = AL_FORMAT_STEREO8;
		}
		else if (bitsPerSample == 16)
		{
			if (channels == 1)
				format = AL_FORMAT_MONO16;
			else if (channels == 2)
				format = AL_FORMAT_STEREO16;
		}
		if (!format) {
			std::cout << "format error" << std::endl;
			return false;
		}
		alBufferData(buffer, format, buf, dataSize, frequency);
		if (alGetError() != AL_NO_ERROR) {
			std::cout << "buffer error" << std::endl;
			return false;
		}

		ALfloat SourcePos[] = { 0.0, 0.0, 0.0 };
		ALfloat SourceVel[] = { 0.0, 0.0, 0.0 };
		ALfloat ListenerPos[] = { 0.0, 0.0, 0.0 };
		ALfloat ListenerVel[] = { 0.0, 0.0, 0.0 };
		ALfloat ListenerOri[] = { 0.0, 0.0, -1.0,  0.0, 1.0, 0.0 };

		alListenerfv(AL_POSITION, ListenerPos);
		alListenerfv(AL_VELOCITY, ListenerVel);
		alListenerfv(AL_ORIENTATION, ListenerOri);

		alSourcei(_source, AL_BUFFER, buffer);
		alSourcef(_source, AL_PITCH, 1.0f);
		alSourcef(_source, AL_GAIN, 1.0f);
		alSourcefv(_source, AL_POSITION, SourcePos);
		alSourcefv(_source, AL_VELOCITY, SourceVel);
		alSourcei(_source, AL_LOOPING, AL_FALSE);
		return true;
	}
}