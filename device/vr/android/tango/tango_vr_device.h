// Copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef DEVICE_VR_TANGO_VR_DEVICE_H
#define DEVICE_VR_TANGO_VR_DEVICE_H

#include <jni.h>

#include "base/android/jni_android.h"
#include "base/macros.h"
#include "device/vr/vr_device.h"

#include "tango_client_api.h"

namespace device {

class TangoVRDeviceProvider;

class TangoVRDevice : public VRDevice {
 public:
  explicit TangoVRDevice(TangoVRDeviceProvider* provider);
  ~TangoVRDevice() override;

  mojom::VRDisplayInfoPtr GetVRDevice() override;
  mojom::VRPosePtr GetPose() override;
  void ResetPose() override;
  mojom::VRPassThroughCameraPtr GetPassThroughCamera() override;
  std::vector<mojom::VRHitPtr> HitTest(float x, float y) override;

  void RequestPresent(const base::Callback<void(bool)>& callback) override;
  void SetSecureOrigin(bool secure_origin) override;
  void ExitPresent() override;
  void SubmitFrame(mojom::VRPosePtr pose) override;
  void UpdateLayerBounds(mojom::VRLayerBoundsPtr left_bounds,
                         mojom::VRLayerBoundsPtr right_bounds) override;

 private:
  TangoCoordinateFramePair tangoCoordinateFramePair;
  TangoVRDeviceProvider* tangoVRDeviceProvider;

  int lastSensorOrientation;
  int lastActivityOrientation;
  DISALLOW_COPY_AND_ASSIGN(TangoVRDevice);
};

}  // namespace device

#endif  // DEVICE_VR_TANGO_VR_DEVICE_H
