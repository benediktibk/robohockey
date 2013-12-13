#include "layer/strategy/common/refereeimpl.h"
#include "extern/angelina/referee.h"
#include "common/point.h"
#include <assert.h>

using namespace RoboHockey::Common;
using namespace RoboHockey::Layer::Strategy::Common;
using namespace Extern::Angelina;

RefereeImpl::RefereeImpl(const std::string &AngelinaAdressServer):
	QObject(0),
	m_trueColorOfTeam(FieldColorUnknown)
{
	m_detectionStart = false;
	m_disconnected = false;
	m_GameStart = false;
	m_GameOver = false;
	m_stopMovement = false;
	m_Connected = false;
	m_ConnectFailed = false;
	m_isValid = false;
	m_referee = new Extern::Angelina::Referee(0);
	connect(m_referee, SIGNAL(disconnected()),this, SLOT(slotDisconneted()));
	connect(m_referee, SIGNAL(detectionStart()),this, SLOT(slotDetectionStart()));
	connect(m_referee, SIGNAL(gameStart()),this, SLOT(slotGameStart()));
	connect(m_referee, SIGNAL(gameOver()),this, SLOT(slotGameOver()));
	connect(m_referee, SIGNAL(trueColorOfTeam(TeamColor)),this, SLOT(slotTrueColorOfTeam(TeamColor)));
	connect(m_referee, SIGNAL(stopMovement()),this, SLOT(slotStopMovement()));
	connect(m_referee, SIGNAL(connected()),this, SLOT(slotConnected()));
	connect(m_referee, SIGNAL(connectFailed()),this, SLOT(slotConnectFailed()));
	m_referee->connectToServer(QString(AngelinaAdressServer.c_str()), 10000);
}

RefereeImpl::~RefereeImpl()
{
	delete m_referee;
	m_referee = 0;
}

void RefereeImpl::reportReady()
{
	m_referee->reportReady();
}

void RefereeImpl::reportDone()
{
	m_referee->reportDone();
}

void RefereeImpl::sendAlive()
{
	m_referee->sendAlive();
}

void RefereeImpl::tellTeamColor(FieldColor color)
{
	TeamColor teamColor = blue;

	if (color == FieldColorBlue)
		teamColor = blue;
	else if (color == FieldColorYellow)
		teamColor = yellow;
	else
		assert(false);

	m_referee->tellTeamColor(teamColor);
}

void RefereeImpl::reportGoal()
{
	m_referee->reportGoal();
}

void RefereeImpl::tellEgoPos(const Point &position)
{
	//! @todo transform into coordinate system of angelina (dependend on team color!)
	m_referee->tellEgoPos(position.getX(),position.getY());
}

bool RefereeImpl::detectionStart()
{
	return m_detectionStart;
}

bool RefereeImpl::gameStart()
{
	return m_GameStart;
}

bool RefereeImpl::gameOver()
{
	return m_GameOver;
}

FieldColor RefereeImpl::trueColorOfTeam()
{
	return m_trueColorOfTeam;
}

bool RefereeImpl::stopMovement()
{
	return m_stopMovement;
}

bool RefereeImpl::isValid()
{
	return m_isValid;
}

void RefereeImpl::slotDisconnected()
{
	m_disconnected = true;
}

void RefereeImpl::slotDetectionStart()
{
	m_detectionStart = true;
	m_GameStart = false;
	m_GameOver = false;
	m_stopMovement = false;
}

void RefereeImpl::slotGameStart()
{
	m_detectionStart = false;
	m_GameStart = true;
	m_GameOver = false;
	m_stopMovement = false;
}

void RefereeImpl::slotGameOver()
{
	m_detectionStart = false;
	m_GameStart = false;
	m_GameOver = true;
	m_stopMovement = true;
}

void RefereeImpl::slotTrueColorOfTeam(TeamColor color)
{
	if (color == blue)
		m_trueColorOfTeam = FieldColorBlue;
	else
		m_trueColorOfTeam = FieldColorYellow;
}

void RefereeImpl::slotStopMovement()
{
	m_detectionStart = false;
	m_GameStart = false;
	m_GameOver = false;
	m_stopMovement = true;
}

void RefereeImpl::slotConnected()
{
	m_Connected = true;
}

void RefereeImpl::slotConnectFailed()
{
	m_ConnectFailed = true;
}
