#include  "session.h"
#include "tag.h"

int main()
{
	int soc_fd;

		if ((soc = setup_server(PORT)) == -1)
			exit(1);
		//セッション
		session_init(soc, 'p',, 1,1,'x',10,10);

		session_loop();
}

