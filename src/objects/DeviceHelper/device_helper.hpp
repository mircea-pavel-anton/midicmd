#ifndef DEVICE_HELPER_CLASS
#define DEVICE_HELPER_CLASS

#include "../MidiHelper/midi_helper.hpp"
#include "../ConfigHelper/config_helper.hpp"
#include "../Utils/utils.hpp"

namespace midicmd {
namespace device {

/**
 * Class that provides limited management functionality when it
 * comes to midi devices.
 * 
 * The provided functionality includes:
 *   - listing all conected devices
 *   - prompting the user to pick one for the service to listen to
 *   - printing the currnetly active device
**/
class DeviceHelper {
	public:
		DeviceHelper() {};
		~DeviceHelper() {};

		void list() const;
		void set() const;
		void set(int) const;
		void status() const;
		void help() const;
}; //DeviceHelper

} //namespace midicmd
} //namespace device

#endif //DEVICE_HELPER_CLASS