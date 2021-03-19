#include <HalonMTA.h>
#include <syslog.h>
#include <memory>
#include <cstring>

char* id = nullptr;

HALON_EXPORT
int Halon_version()
{
	return HALONMTA_PLUGIN_VERSION;
}

HALON_EXPORT
bool Halon_init(HalonInitContext* hic)
{
	id = HalonMTA_queue_suspend_add(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, "START_SUSPEND", 0);
	if (!id)
		return false;
	syslog(LOG_INFO, "startpaused: %s", id);
	return true;
}

HALON_EXPORT
bool Halon_plugin_command(const char* in, size_t len, char** out, size_t* olen)
{
	*out = strdup(id);
	return true;
}

HALON_EXPORT
void Halon_cleanup()
{
	if (id)
		free(id);
}
