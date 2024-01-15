#include <mmdeviceapi.h>
#include <audioclient.h>
#include <ole2.h>
#include <windows.h>
#include<mmreg.h>
#include <avrt.h>
#include <stdio.h>


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

void getaud(){
	IMMDeviceEnumerator *deviceEnuerator;
	IMMDevice *immdevice;
	IAudioClient *iaudioclient;
	IAudioCaptureClient *captureclient;

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

if(iaudioclient->lpVtbl->GetService(iaudioclient, &IID_IAudioCaptureClient, (void**)&captureclient)){
	MessageBox(NULL, "audio service not gotten", "audio service", MB_OK);
}else{MessageBox(NULL, "audio service gotten", "audio service", MB_OK);}

if(iaudioclient->lpVtbl->Start(iaudioclient)){
	MessageBox(NULL, "audio not started", "audio not started", MB_OK);
}else{MessageBox(NULL, "audio started", "audio started", MB_OK);}

while(1){
	BYTE *pData;
UINT32 framesAvailable;
DWORD flags;

if(captureclient->lpVtbl->GetBuffer(captureclient, &pData, &framesAvailable, &flags, NULL, NULL)){
	MessageBox(NULL, "not getting buffer", "frames buffer", MB_OK);
}else{MessageBox(NULL, "getting buffer", "frames buffer", MB_OK); }

if(framesAvailable>0){
	char framesgetter[100];
	MessageBox(NULL, "getting frames", "frames getter", MB_OK);
	for(UINT32 i = 0; i<framesAvailable; i++){
		 int sampleValue = ((int*)pData)[i];
		sprintf(framesgetter, "%d", sampleValue);
		MessageBox(NULL, framesgetter, "current sample", MB_OK);
	}
	
}



}

}



int main(){
	IAudioClient *iaudioclient = NULL;

    getaud();
    if(!iaudioclient){
    	MessageBox(NULL, "audio client not null", "audio client", MB_OK);
    }else{MessageBox(NULL, "audioclient null", "audio client", MB_OK);}
	return 0;
}
