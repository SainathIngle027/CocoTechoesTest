#include <bits/stdc++.h>
using namespace std;

vector<string> cities = {"Pune", "Mumbai", "Nanded", "Latur", "Nashik"};
vector<string> daystamp = {"Morning", "Afternoon", "Evening", "Light"};

// Define structure for visit entry
struct VisitEntry {
    int userId;
    string timeOfDay;
    int timeSpentMinutes;
};

// Generate web traffic data
vector<vector<VisitEntry>> generateWebTrafficData(int numCities, int numEntriesPerCity) {
    vector<vector<VisitEntry>> webTrafficData(numCities);

    for (int i = 0; i < numCities; ++i) {
        for (int j = 0; j < numEntriesPerCity; ++j) {
            VisitEntry entry = {
                // Userid from [1-30]
                rand() % 30 + 1,
                // Vector string daystamp
                daystamp[rand() % 4],
                // Timespend 
                rand() % 60
            };

            webTrafficData[i].push_back(entry);
        }
    }

    return webTrafficData;
}

// Print web traffic data
void printWebTrafficData(const vector<vector<VisitEntry>>& webTrafficData) {
    for (int i = 0; i < webTrafficData.size(); ++i) {
        cout << "City: " << cities[i] << endl;
        for (const auto& entry : webTrafficData[i]) {
            cout << "User ID: " << entry.userId << ", Time of Day: " << entry.timeOfDay
                 << ", Time Spent (minutes): " << entry.timeSpentMinutes << endl;
        }
        cout << "------------------------" << endl;
    }
}

//time of day with the most number of unique users
pair<string, int> findPeakTime(const vector<vector<VisitEntry>>& webTrafficData) {
    unordered_map<string, unordered_set<int>> timeOfDayUsers;

    for (const auto& cityData : webTrafficData) {
        for (const auto& entry : cityData) {
            timeOfDayUsers[entry.timeOfDay].insert(entry.userId);
        }
    }

    auto maxTimeOfDay = max_element(timeOfDayUsers.begin(), timeOfDayUsers.end(),
        [](const pair<string, unordered_set<int>>& a, const pair<string, unordered_set<int>>& b) {
            return a.second.size() < b.second.size();
        });

    return make_pair(maxTimeOfDay->first, maxTimeOfDay->second.size());
}

// city that uses the site most at a specific time of day
pair<string, string> findCityWithMaxUsage(const vector<vector<VisitEntry>>& webTrafficData, const string& timeOfDay) {
    unordered_map<string, int> cityUsageCount;

    for (int i = 0; i < webTrafficData.size(); ++i) {
        for (const auto& entry : webTrafficData[i]) {
            if (entry.timeOfDay == timeOfDay) {
                cityUsageCount[cities[i]]++;
            }
        }
    }

    auto maxCity = max_element(cityUsageCount.begin(), cityUsageCount.end(),
        [](const pair<string, int>& a, const pair<string, int>& b) {
            return a.second < b.second;
        });

    return make_pair(maxCity->first, timeOfDay);
}

int main() {
    auto webTrafficData = generateWebTrafficData(5, 100);
    printWebTrafficData(webTrafficData);
    
    // time of day with the most number of unique users
    auto peakTime = findPeakTime(webTrafficData);
    auto maxCityUsage = findCityWithMaxUsage(webTrafficData, peakTime.first);
    cout << "Time of day with the most users : " << peakTime.first << " - " << maxCityUsage.first  << " , Users count: " << peakTime.second << endl;


    cout << "\nTest done !! \nThank You" << endl;

    return 0;
}
