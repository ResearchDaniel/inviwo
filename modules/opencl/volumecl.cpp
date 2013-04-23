#include <modules/opencl/volumecl.h>

namespace inviwo {

VolumeCL::VolumeCL(DataFormatBase format)
    :  VolumeRepresentation(uvec3(128,128,128), format), image3D_(0)
{
}

VolumeCL::VolumeCL(uvec3 dimensions, DataFormatBase format)
    : image3D_(0), VolumeRepresentation(dimensions, format)
{
}

VolumeCL::~VolumeCL() {}


} // namespace

namespace cl {

template <>
cl_int Kernel::setArg(cl_uint index, const inviwo::VolumeCL& value)
{
    return setArg(index, value.getVolume());
}


} // namespace cl
