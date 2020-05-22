/* Please note: even though it says IMPLEMENT ME, in some cases
   the implementation can be empty. In fact, you may wish to remove
   some of the functions entirely
*/
#include "Football.h"

// -------------- Team --------------------

Team::Team(const string& name) {
  teamName_ = name;
  goalsCon_ = 0;
}

void Team::addGoalsConceded(int g) {
  goalsCon_ += g;
}

int Team::getGoalsCon() const {
  return goalsCon_;
}

string Team::getTeamName(Team* t) const {
  return teamName_;
}

Team::~Team() {
  // IMPLEMENT ME
}

// -------------- Player ------------------

Player::Player() {
  // see comment in .h
}

Player::Player(const string& name, Team* t) {
  playerName_ = name;
  playerTeam_ = t;
  playerGoals_ = 0;
  playerAssists_ = 0;
}

// don't remove this even if you want to make the destructor pure virtual
Player::~Player() {
	// IMPLEMENT ME
}

void Player::addGoalsScored(int g) {
  playerGoals_ += g;
}

void Player::addAssists(int a) {
  playerAssists_ += a;
}

//Note: the getScore() function was made virtual and removed from the base class

string Player::print() const {
  //below is just stub code
  string removeMe = "";
  return removeMe;
}

// -------------- Attacker ------------------

Attacker::Attacker(const string& name, Team* t):Player(name, t) {
  stats_ = "";
}

Attacker::~Attacker() {
	// IMPLEMENT ME
}

int Attacker::getScore() const {
  int attScore = 0;
  attScore = (4*playerGoals_) + (3*playerAssists_);
  return attScore;
}

string Attacker::print() const {
  //Prints blank output will not print correctly
  //(despite code printing for Goalkeeper)
  string name = playerName_;
  string team = this->playerTeam_->getTeamName(playerTeam_);
  string goals = to_string(this->playerGoals_);
  string assists = to_string(this->playerAssists_);
  string goalsCon = to_string(this->playerTeam_->getGoalsCon());
  string score = to_string(this->getScore());
  string stats_ = "Attacker: " + name +  ", Team: " + team + "\n";
  stats_ += " Goals scored: " + goals + "\n";
  stats_ += " Assists: " + assists + "\n";
  stats_ += " Goals conceded: " + goalsCon + "\n";
  stats_ += " Score: " + score;
  return stats_;
}


// -------------- Midfielder ------------------

Midfielder::Midfielder(const string& name, Team* t):Player(name, t) {
  stats_ = "";
}

Midfielder::~Midfielder() {
	// IMPLEMENT ME
}

int Midfielder::getScore() const {
  int midFGoalsCon = playerTeam_->getGoalsCon();
  int midFScore = (5*playerGoals_) + (3*playerAssists_);
   if (midFGoalsCon == 0){
	 midFScore += 1;
	 return midFScore;
       }
  return midFScore;
}

string Midfielder::print() const {
  //Prints blank output will not print correctly
  //(despite code printing for Goalkeeper)
  string name = this->playerName_;
  string team = this->playerTeam_->getTeamName(playerTeam_);
  string goals = to_string(this->playerGoals_);
  string assists = to_string(this->playerAssists_);
  string goalsCon = to_string(this->playerTeam_->getGoalsCon());
  string score = to_string(this->getScore());
  string stats_ = "Midfielder: " + name + ", Team: " + team + "\n";
  stats_ += " Goals scored: " + goals + "\n";
  stats_ += " Assists: " + assists + "\n";
  stats_ += " Goals conceded: " + goalsCon + "\n";
  stats_ += " Score: " + score;
  return stats_;
}

// -------------- Defender ------------------

Defender::Defender(const string& name, Team* t):Player(name, t) {
}

Defender::~Defender() {
	// IMPLEMENT ME
}

int Defender::getScore() const {
       int defGoalsCon = playerTeam_->getGoalsCon();
       int defScore = (6*playerGoals_) + (3*playerAssists_) - (defGoalsCon/2);
       if (defGoalsCon == 0){
	 defScore += 4;
	 return defScore;
       }
       return defScore;
}

string Defender::print() const {
  //Prints blank output will not print correctly
  //(despite code printing for Goalkeeper)
  string name = this->playerName_;
  string team = this->playerTeam_->getTeamName(playerTeam_);
  string goals = to_string(this->playerGoals_);
  string assists = to_string(this->playerAssists_);
  string goalsCon = to_string(this->playerTeam_->getGoalsCon());
  string score = to_string(this->getScore());
  string stats_ = "Defender: " + name + ", Team: " + team + "\n";
  stats_ += " Goals scored: " + goals + "\n";
  stats_ += " Assists: " + assists + "\n";
  stats_ += " Goals conceded: " + goalsCon + "\n";
  stats_ += " Score: " + score;
  return stats_;
}

// -------------- Goalkeeper ------------------

Goalkeeper::Goalkeeper(const string& name, Team* t):Player(name, t) {
  shotSaved_ = 0;
}

Goalkeeper::~Goalkeeper() {
	// IMPLEMENT ME
}

void Goalkeeper::addShotsSaved(int ss) {
  shotSaved_ += ss;
}

int Goalkeeper::getScore() const {
       int gKeepGoalsCon = playerTeam_->getGoalsCon();
       int gKeepScore = (6*playerGoals_) + (3*playerAssists_) - (gKeepGoalsCon/2) + (shotSaved_/3);
       if (gKeepGoalsCon == 0){
	 gKeepScore += 4;
	 return gKeepScore;
       }
       return gKeepScore;
}

string Goalkeeper::print() const {
  string name = this->playerName_;
  string team = this->playerTeam_->getTeamName(playerTeam_);
  string goals = to_string(this->playerGoals_);
  string assists = to_string(this->playerAssists_);
  string goalsCon = to_string(this->playerTeam_->getGoalsCon());
  string score = to_string(this->getScore());
  string saved = to_string(this->shotSaved_);
  string stats_ = "Goalkeeper: " + name + ", Team: " + team + "\n";
  stats_ += " Goals scored: " + goals + "\n";
  stats_ += " Assists: " + assists + "\n";
  stats_ += " Goals conceded: " + goalsCon + "\n";
  stats_ += " Shots saved: " + saved + "\n";
  stats_ += " Score: " + score;
  return stats_;
}

// -------------- FantasyTeam ------------------

FantasyTeam::FantasyTeam() {
  playerLimit_ = 11;
  for (int i = 0; i < playerLimit_; i++){
    players[i] = nullptr;
  }
  numPlayers_ = 0;
  
}

FantasyTeam::~FantasyTeam() {
	// IMPLEMENT ME
}

bool FantasyTeam::addPlayer(Player* p) {
  if((notDuplicatePlayer(p)) && (numPlayers_ < playerLimit_)){
    players[numPlayers_] = p;
    numPlayers_ += 1;
    return true;
  }
  return false;
}

bool FantasyTeam::notDuplicatePlayer(Player* p){
  //check that player to be added is not a duplicated player.
  bool notDuplicate = false;
  for (int i = 0; i < numPlayers_; i++){
     if(players[i] != p){
        notDuplicate = true;
     }else{
       return false;
     }
  }
  return notDuplicate;
}

int FantasyTeam::getScore() const {
  //Code may function but relies on players being sucessfully added.
  int ftScore = 0;
  if(numPlayers_ != 0){
    for (int i = 0;i < numPlayers_; i++){
      if(players[i] == nullptr){
	ftScore += 0;
      }else{
	ftScore += players[i]->getScore();
      }
    }
  }
  return ftScore;
}
