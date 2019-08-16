#include <iostream>
#include <map>
#include <deque>

using namespace std;

struct Event {
    Event(size_t id, long long time, size_t count)
        : client_id_(id),
        time_(time),
        room_count_(count) {}

    size_t client_id_;
    long long time_;
    size_t room_count_;
};

class Booking {
public:
    Booking()
        : current_time(-1'000000'000000'000000),
        rooms(0) {};

    void Book(Event& e) {
        ++room_count[e.client_id_];
        events.push_back(e);
        rooms += e.room_count_;

        Update(e.time_);
    }

    size_t Clients(long long time) {
        Update(time);
        return room_count.size();
    }

    size_t Rooms(long long time) {
        Update(time);
        return rooms;
    }

private:
    long long current_time;
    map<size_t, size_t> room_count;
    deque<Event> events;
    size_t rooms;

    void Update(long long time) {
        current_time = time;
        while (!events.empty() && events.front().time_ <= current_time - 86400) {
            if (room_count[events.front().client_id_] == 1) {
                room_count.erase(events.front().client_id_);
            } else {
                --room_count[events.front().client_id_];
            }

            rooms -= events.front().room_count_;
            events.pop_front();
        }
    }
};



int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    size_t query;
    cin >> query;

    map<string, Booking> booking;
    long long current_time = -1'000000'000000'000000;

    for (size_t i = 0; i < query; ++i) {
        string query_type;
        cin >> query_type;
        if (query_type == "BOOK") {
            size_t id;
            size_t count;
            long long time;
            string name;
            cin >> time >> name >> id >> count;
            current_time = time;
            Event e(id, time, count);
            booking[name].Book(e);
        } else if (query_type == "CLIENTS") {
            string name;
            cin >> name;
            cout << booking[name].Clients(current_time) << '\n';
        } else if (query_type == "ROOMS") {
            string name;
            cin >> name;
            cout << booking[name].Rooms(current_time) << '\n';
        }
    }

    return 0;
}