#include <HalonMTA.h>
#include <syslog.h>
#include <memory>
#include <cstring>
#include <cstdlib>

char* id = nullptr;

HALON_EXPORT
int Halon_version()
{
	return HALONMTA_PLUGIN_VERSION;
}

HALON_EXPORT
bool Halon_init(HalonInitContext* hic)
{
	id = HalonMTA_queue_suspend_add(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, "SUSPEND_START", 0);
	if (!id)
		return false;
	syslog(LOG_INFO, "suspend start: %s", id);
	return true;
}

HALON_EXPORT
bool Halon_command_execute(HalonCommandExecuteContext* hcec, size_t argc, const char* argv[], size_t argvl[], char** out, size_t* outlen)
{
	if (argc > 0 && strcmp(argv[0], "getid") == 0)
	{
		if (!id)
			return false;
		*out = strdup(id);
		return true;
	}
	if (argc > 0 && strcmp(argv[0], "start") == 0)
	{
		if (!id)
			return false;
		bool r = HalonMTA_queue_suspend_delete(id);
		free(id);
		id = nullptr;
		return r;
	}
	return false;
}

HALON_EXPORT
void Halon_cleanup()
{
	if (id)
		free(id);
}
