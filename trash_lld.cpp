#include<bits/stdc++.h>
using namespace std;

struct Event {
	int eid;
	int start;
	int end;
	string location;
	int ownerId;
	unordered_map<int, int> accepted_or_declined; // (Key) uid : (Value) 1 - Accepted, 0 - Neutral, -1, Declined
	int type;
	Event(int eid, int start,int end, int type, string location, int ownerId) : eid(eid), start(start), end(end), location("no location specified"), type(type), ownerId(ownerId) {}; 
};

struct User {
	string name;
	int uid;
	User(int uid, string name) : uid(uid), name(name) {};
	unordered_map<Event*, int> attending_events; // EventID - (Value) 1 - Accepted, 0 - Neutral, -1, Declined
};

void updateTimings(Event& currEvent, int newStart, int newEnd) {
	currEvent.start = newStart;
	currEvent.end = newEnd;
}

void updateLocation(Event& currEvent, string newLocation) {
	currEvent.location = newLocation;
}

void updateUsers(Event* currEvent, User& user, string type = "add") {
	unordered_map<int, int> currEventUsers = currEvent->accepted_or_declined;
	if(currEventUsers.find(user.uid) == currEventUsers.end() && type == "add") {
		currEvent->accepted_or_declined[user.uid] = 0;
		user.attending_events[currEvent] = 0;
	} else {
		cout << "User" << user.name << " is already in the event\n";
	}
}

void respondToEvent(User& user, Event* event, string response = "ACCEPT") {
	int responseId = (response == "ACCEPT") ? 1 : -1;
	if(event->accepted_or_declined.find(user.uid) != event->accepted_or_declined.end()) {
		event->accepted_or_declined[user.uid] = responseId;
		user.attending_events[event] = responseId;
	} else {
		cout << "UserId " << user.name << " is not even a part of the event\n";
	}
}


vector<Event*> getEventsWithin(User& user, int start, int end) {
	if(start >= end) {
		cout << "Invalid duration\n";
		return {};
	}
	vector<Event*> ans;
	for(auto it : user.attending_events) {
		Event* evt = it.first;
		if(evt->start >= start && evt->end <= end) {
			ans.push_back(evt);
		}
	}
	return ans;
}


int main() { 
	unordered_map<int, string> EVENT_TYPES;
	EVENT_TYPES[0] = "holiday";//
	User maint(100, "Maint");
	Event e1(1,0,3, 0, "xyz", 100);
	Event e2(2,4,6, 0, "abc", 100);
	updateTimings(e1, 1, 4);
	updateLocation(e1, "BLR");
	User u1(1, "User1");
	User u2(2, "User2");
	User u3(3, "User3");
	updateUsers(&e1, u2);

	updateUsers(&e1, u1);
	updateUsers(&e1, u3);

	updateUsers(&e2, u2);
	updateUsers(&e2, u3);
	//
	respondToEvent(u2,&e1);
	respondToEvent(u1,&e1);
	respondToEvent(u3,&e1);
	respondToEvent(u2, &e2);
	respondToEvent(u3, &e2);
	//respondToEvent(u3,&e1, "DECLINE");

	vector<Event*> ans = getEventsWithin(u2, 1, 5);
	cout << "Events within window \n";
	for(auto it : ans) {
		cout << it->eid << endl;
	}
	return 0;
}
