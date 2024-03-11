
#include <mmdeviceapi.h>
#include <audioclient.h>
#include <ole2.h>
#include <windows.h>
#include<mmreg.h>
#include <avrt.h>
#include <stdio.h>
#include <time.h>
#include "readfile.h"


static const GUID		IID_IAudioClient = {0x1CB9AD4C, 0xDBFA, 0x4c32, 0xB1, 0x78, 0xC2, 0xF5, 0x68, 0xA7, 0x03, 0xB2};
static const GUID		IID_IAudioRenderClient = {0xF294ACFC, 0x3146, 0x4483, 0xA7, 0xBF, 0xAD, 0xDC, 0xA7, 0xC2, 0x60, 0xE2};
static const GUID		CLSID_MMDeviceEnumerator = {0xBCDE0395, 0xE52F, 0x467C, 0x8E, 0x3D, 0xC4, 0x57, 0x92, 0x91, 0x69, 0x2E};
static const GUID		IID_IMMDeviceEnumerator = {0xA95664D2, 0x9614, 0x4F35, 0xA7, 0x46, 0xDE, 0x8D, 0xB6, 0x36, 0x17, 0xE6};
static const GUID       IID_IAudioCaptureClient = { 0xc8ADBD64, 0xE71E, 0x48A0,0xA4, 0xdE, 0x18, 0x5C, 0x39, 0x5C, 0xD3, 0x17};
static const GUID		PcmSubformatGuid = {STATIC_KSDATAFORMAT_SUBTYPE_PCM};
REFERENCE_TIME bufferduration;
REFERENCE_TIME periodicity;
static WCHAR *DevID;
UINT32 bufferframecount;

IMMDeviceEnumerator *deviceEnuerator;
	IMMDevice *immdevice;
	IAudioClient *iaudioclient;
	IAudioCaptureClient *captureclient;
	IAudioRenderClient* renderClient;
	WAVEFORMATEX *wave;
	UINT32 buffercount = 448;
	UINT32 currentpadding;




void activate_getting_port(){
	

	CoInitialize(0);


	if(CoCreateInstance(&CLSID_MMDeviceEnumerator, 0, CLSCTX_INPROC_SERVER, &IID_IMMDeviceEnumerator, (void**) &deviceEnuerator)){
	MessageBox(NULL, "Model", "Model not opened successfully!", MB_OK);
	
	} else{ MessageBox(NULL, "Cocreateinstance", "Instance created successfully!", MB_OK);}	

	if(DevID){
		if(deviceEnuerator->lpVtbl->GetDevice(deviceEnuerator, DevID, &immdevice)){
			MessageBox(NULL, "Device Object", "Cant get iMM device object", MB_OK);
			deviceEnuerator->lpVtbl->Release(deviceEnuerator);
		}else{MessageBox(NULL, "Device Object", "gottten device object", MB_OK);}
	}else{
		if(deviceEnuerator->lpVtbl->GetDefaultAudioEndpoint(deviceEnuerator, eCapture, eMultimedia, &immdevice)){
			MessageBox(NULL, "Couldnt get default audio endpoint", "Audio Endpoint", MB_OK);
		}else{MessageBox(NULL, "gotten default audio endpoint", "Audio Endpoint", MB_OK);}
	}

	if(immdevice->lpVtbl->Activate(immdevice, &IID_IAudioClient, CLSCTX_INPROC_SERVER, 0, (void**) &iaudioclient)){MessageBox(NULL, "Audio device not Activated", "Audio activator", MB_OK);}else{MessageBox(NULL, "Audio device activated", "Audio activator", MB_OK);}



	if(iaudioclient->lpVtbl->GetMixFormat(iaudioclient, &wave)){
		MessageBox(NULL, "couldnt get format", "audio format", MB_OK);
	}else{
		MessageBox(NULL, "gotten format", "audio format", MB_OK);
	}

	if(iaudioclient->lpVtbl->GetDevicePeriod(iaudioclient, &bufferduration, &periodicity)){
	 MessageBox(NULL, "Failed to get device period", "Error", MB_OK);
}else{
	bufferduration = bufferduration/1000;
	periodicity = periodicity/1000;
	char noted[100];
	sprintf(noted, "the value is %I64d, %I64d %d",bufferduration, periodicity, wave->wBitsPerSample);
	MessageBox(NULL, noted, "minimum duration", MB_OK);
}

if(iaudioclient->lpVtbl->Initialize(iaudioclient, AUDCLNT_SHAREMODE_SHARED, 0, bufferduration, periodicity,wave, 0)){
	 MessageBox(NULL, "audio client not initialized", "initialization error", MB_OK);
}else{MessageBox(NULL, "audio client initialized", "initialization worked", MB_OK);}

if(iaudioclient->lpVtbl->GetBufferSize(iaudioclient, &bufferframecount)){
	MessageBox(NULL, "couldnt get buffersize", "buffer size", MB_OK);
}else{
    char buffersize[100];
    sprintf(buffersize, "gotten buffer size %d", bufferframecount);
	MessageBox(NULL, buffersize, "buffer size", MB_OK);
}

if(iaudioclient->lpVtbl->GetService(iaudioclient, &IID_IAudioCaptureClient, (void**)&captureclient)){
	MessageBox(NULL, "audio service not gotten", "audio service", MB_OK);
}else{MessageBox(NULL, "audio service gotten for capture", "audio service", MB_OK);}

if(iaudioclient->lpVtbl->Start(iaudioclient)){
	MessageBox(NULL, "audio not started", "audio not started", MB_OK);
}else{MessageBox(NULL, "audio started for capture", "audio started", MB_OK);}

}




void activate_listen_port(){


	CoInitialize(0);


	if(CoCreateInstance(&CLSID_MMDeviceEnumerator, 0, CLSCTX_INPROC_SERVER, &IID_IMMDeviceEnumerator, (void**) &deviceEnuerator)){
	MessageBox(NULL, "Model", "Model not opened successfully!", MB_OK);
	
	} else{ MessageBox(NULL, "Cocreateinstance", "Instance created successfully!", MB_OK);}	

	if(DevID){
		if(deviceEnuerator->lpVtbl->GetDevice(deviceEnuerator, DevID, &immdevice)){
			MessageBox(NULL, "Device Object", "Cant get iMM device object", MB_OK);
			deviceEnuerator->lpVtbl->Release(deviceEnuerator);
		}else{MessageBox(NULL, "Device Object", "gottten device object", MB_OK);}
	}else{
		if(deviceEnuerator->lpVtbl->GetDefaultAudioEndpoint(deviceEnuerator, eRender, eMultimedia, &immdevice)){
			MessageBox(NULL, "Couldnt get default audio endpoint", "Audio Endpoint", MB_OK);
		}else{MessageBox(NULL, "gotten default audio endpoint", "Audio Endpoint", MB_OK);}
	}

	if(immdevice->lpVtbl->Activate(immdevice, &IID_IAudioClient, CLSCTX_INPROC_SERVER, 0, (void**) &iaudioclient)){MessageBox(NULL, "Audio device not Activated", "Audio activator", MB_OK);}else{MessageBox(NULL, "Audio device activated", "Audio activator", MB_OK);}


	WAVEFORMATEX *wave;

	if(iaudioclient->lpVtbl->GetMixFormat(iaudioclient, &wave)){
		MessageBox(NULL, "couldnt get format", "audio format", MB_OK);
	}else{
		MessageBox(NULL, "gotten format", "audio format", MB_OK);
	}

	if(iaudioclient->lpVtbl->GetDevicePeriod(iaudioclient, &bufferduration, &periodicity)){
	 MessageBox(NULL, "Failed to get device period", "Error", MB_OK);
}else{
	bufferduration = bufferduration/1000;
	periodicity = periodicity/1000;
	char noted[100];
	sprintf(noted, "the value is %I64d, %I64d %d",bufferduration, periodicity, wave->wBitsPerSample);
	MessageBox(NULL, noted, "minimum duration", MB_OK);
}

if(iaudioclient->lpVtbl->Initialize(iaudioclient, AUDCLNT_SHAREMODE_SHARED, 0, bufferduration, periodicity,wave, 0)){
	 MessageBox(NULL, "audio client not initialized", "initialization error", MB_OK);
}else{MessageBox(NULL, "audio client initialized", "initialization worked", MB_OK);}

if(iaudioclient->lpVtbl->GetBufferSize(iaudioclient, &bufferframecount)){
	MessageBox(NULL, "couldnt get buffersize", "buffer size", MB_OK);
}else{
    char buffersize[100];
    sprintf(buffersize, "gotten buffer size %d", bufferframecount);
	MessageBox(NULL, buffersize, "buffer size", MB_OK);
}

if(iaudioclient->lpVtbl->GetService(iaudioclient, &IID_IAudioRenderClient, (void**)&renderClient)){
	MessageBox(NULL, "audio service not gotten", "audio service", MB_OK);
}else{MessageBox(NULL, "audio gotten for rendering", "audio service", MB_OK);}

if(iaudioclient->lpVtbl->Start(iaudioclient)){
	MessageBox(NULL, "audio not started", "audio not started", MB_OK);
}else{ printf("audio started\n"); /*play_audio_samples;*/ Sleep(500); MessageBox(NULL, "audio started for rendering", "audio started", MB_OK);}

}


void play_audio_samples(){
	activate_listen_port();

	printf("loading audio generator...");

	BYTE *rData;
	UINT32 rframesAvailable;
	DWORD rflags;

	HANDLE dataReadyEvent = NULL;
	
	 while (1) {
	 	 WaitForSingleObject(dataReadyEvent, INFINITE);

	 	 if(iaudioclient->lpVtbl->GetCurrentPadding(iaudioclient, &currentpadding)){
	 	 	MessageBox(NULL, "not gottten rendering padding alignment", "audio rendering padding", MB_OK);
	 	 }else{
	 	 	MessageBox(NULL, "gottten rendering padding alignment", "audio rendering padding", MB_OK);
	 	 }
	 	 if(renderClient->lpVtbl->GetBuffer(renderClient, buffercount, &rData)){
	 	 	MessageBox(NULL, "not gottten rendering buffer", "audio rendering buffer", MB_OK);
	 	 }else{
	 	 	MessageBox(NULL, "gottten rendering buffer", "audio rendering buffer", MB_OK);
	 	 	entry(rData, buffercount);
	 	 }
	 	}
    
}





void get_audio_samples(){

	activate_getting_port();


while(1){

	BYTE *pData;
UINT32 framesAvailable;
DWORD flags;
UINT32 i = 0;


	
if(captureclient->lpVtbl->GetBuffer(captureclient, &pData, &framesAvailable, &flags, NULL, NULL))
	MessageBox(NULL, "not getting buffer", "frames buffer", MB_OK);

printf("buffer frame count ==>%u\n", framesAvailable);

memset(pData, 0, framesAvailable * sizeof(BYTE));


if(framesAvailable>0){
	char framesgetter[100];
	for(i; i<framesAvailable; i++){
		 int sampleValue = ((int*)pData)[i];
		sprintf(framesgetter, "%d", sampleValue);
		FILE *file;
		file = fopen("data.txt", "a");
		if(file == NULL)
			printf("file not opened successfully");
		printf("%u\n", sampleValue);
		fprintf(file, "%u\n", sampleValue);
		fclose(file);

		
	}

	printf("Final value of i: %u\n", i);

	 captureclient->lpVtbl->ReleaseBuffer(captureclient, framesAvailable);
	
}

}

}





int main(){

	 //get_audio_samples();
	

	//printf("file opened successfully");

	//IAudioClient *iaudioclient = NULL;

	play_audio_samples();

    //if(!iaudioclient){
    //	MessageBox(NULL, "audio client not null", "audio client", MB_OK);
    //}else{MessageBox(NULL, "audioclient null", "audio client", MB_OK);}*/

    //sound_store();
	return 0;
}