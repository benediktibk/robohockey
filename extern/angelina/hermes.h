#ifndef ROBOHOCKEY_EXTERN_ANGELINA_HERMES_H
#define ROBOHOCKEY_EXTERN_ANGELINA_HERMES_H

#include <QtNetwork/QTcpSocket>

#include "hermescodes.h"

namespace Extern
{
namespace Angelina
{
	class Referee;

	class Hermes:
			public QTcpSocket
	{
		Q_OBJECT

		public:
			Hermes(QObject *parent = 0);
			~Hermes();

		private:
			Referee *referee;
			int myTeamID;
			int messageSize;
	};
}
}
#endif
