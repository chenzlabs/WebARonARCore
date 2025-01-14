/*
 * Copyright 2016 Google Inc. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _TANGO_HANDLER_H_
#define _TANGO_HANDLER_H_

#include "tango_client_api.h"   // NOLINT
#include "tango_client_api2.h"   // NOLINT
#include "tango_support.h"  // NOLINT

#include <ctime>

#include <jni.h>
#include <android/log.h>

#include <string>
#include <vector>
#include <queue>

#include <mutex>

#define LOG_TAG "LeTango Chromium"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

namespace tango_chromium {

class Hit
{
public:
	float modelMatrix[16];
};

// TangoHandler provides functionality to communicate with the Tango Service.
class TangoHandler {
public:
	static TangoHandler* getInstance();
	static void releaseInstance();

	TangoHandler();

	TangoHandler(const TangoHandler& other) = delete;
	TangoHandler& operator=(const TangoHandler& other) = delete;

	~TangoHandler();

	void onCreate(JNIEnv* env, jobject activity, int activityOrientation, int sensorOrientation);
	void onTangoServiceConnected(JNIEnv* env, jobject tango);
	void onPause();
	void onDeviceRotationChanged(int activityOrientation, int sensorOrientation);
	void onTangoEventAvailable(const TangoEvent* event);

	bool isConnected() const;

	bool getPose(TangoPoseData* tangoPoseData);
	bool getProjectionMatrix(float near, float far, float* projectionMatrix);
	bool hitTest(float x, float y, std::vector<Hit>& hits);
	void resetPose();

	bool updateCameraIntrinsics();
	bool getCameraImageSize(uint32_t* width, uint32_t* height);
	bool getCameraImageTextureSize(uint32_t* width, uint32_t* height);
	bool getCameraFocalLength(double* focalLengthX, double* focalLengthY);
	bool getCameraPoint(double* x, double* y);
	bool updateCameraImageIntoTexture(uint32_t textureId);

	int getSensorOrientation() const;
	int getActivityOrientation() const;

private:
	void connect();
	void disconnect();
	bool hasLastTangoImageBufferTimestampChangedLately();

	static TangoHandler* instance;

	bool connected;
	TangoConfig tangoConfig;
	TangoCameraIntrinsics tangoCameraIntrinsics;
	double lastTangoImageBufferTimestamp;
	std::time_t lastTangoImagebufferTimestampTime;

	uint32_t cameraImageWidth;
	uint32_t cameraImageHeight;
	uint32_t cameraImageTextureWidth;
	uint32_t cameraImageTextureHeight;

	bool textureIdConnected;

	int activityOrientation;
	int sensorOrientation;

	std::string tangoCoreVersionString;
};

}  // namespace tango_4_chromium

#endif  // _TANGO_HANDLER_H_
