#ifndef ACT_PLN_SMS
#define ACT_PLN_SMS
class StatesMachines
{
public:
	/*
	* Enum to represent the SMs status
	*
	*/
	enum SM_STATUS
	{
		Initializing,
		Executing,
		Succeeded,
		Failed
	};
	
	SM_STATUS objectPerceptionSM();
//private:
};
#endif
