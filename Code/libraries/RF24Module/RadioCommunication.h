
enum SensorValue
{
	Temperature,
	Lighting,
	Rain,
	Humidity,
	Pressure,
	Voltage
};

enum WarningType
{
	LowVoltage,
	HighTemperature,
	LowTemperature,
	LowMemory
};

enum RequestType
{
	RequestSensorValue,
	CapturedSensorValue,
	UpTime,
	Time,
	FreeMemory,
	Warning
};


struct RadioRequest
{
	RequestType Type;

	double Parameter;

	static RadioRequest Create(RequestType type, double parameter = 0)
	{
		RadioRequest request;
		request.Type = type;
		request.Parameter = parameter;

		return request;
	}
};

enum ResponseStatus
{
	Ok,
	Timeout
};

struct RadioResponse
{
	ResponseStatus Status;

	double Value;

	static RadioResponse CreateSuccesfull(double value)
	{
		RadioResponse response;
		response.Status = Ok;
		response.Value = value;

		return response;
	}

	static RadioResponse CreateUnsuccesfull(ResponseStatus status)
	{
		RadioResponse response;
		response.Status = status;

		return response;
	}
};