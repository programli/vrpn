#include  "vrpn_Analog.h"

class vrpn_Nikon_Controls : public vrpn_Serial_Analog {
public:
  vrpn_Nikon_Controls(const char *device_name, vrpn_Connection *con = NULL, const char *port_name = "com1");
  ~vrpn_Nikon_Controls(void) {};

  virtual void mainloop ();

protected:
  int _status;

  unsigned char _buffer[512]; //< Buffer of characters in report
  int _bufcount;	      //< How many characters we have so far

  double  _requested_focus;   //< Where we asked the focus to be set to

  struct timeval timestamp;   //< Time of the last report from the device

  virtual int reset(void);		//< Set device back to starting config
  virtual int get_report(void);		//< Try to read a report from the device

  /// Send changes since the last time
  virtual void report_changes (vrpn_uint32 class_of_service = vrpn_CONNECTION_LOW_LATENCY);

  /// Send values whether or not they have changed.
  virtual void report (vrpn_uint32 class_of_service = vrpn_CONNECTION_LOW_LATENCY);

  /// Responds to a request to change one of the values by
  /// setting the channel to that value.
  static int handle_request_message(void *userdata, vrpn_HANDLERPARAM p);

  /// Responds to a connection request with a report of the values
  static int handle_connect_message(void *userdata, vrpn_HANDLERPARAM p);

};

