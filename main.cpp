#include <iostream>
#include <map>
#include <tuple>
#include <vector>
#include <string>
#include <limits>
using namespace std;

using VillagerData = tuple<int, string, string>;
using VillagerMap  = map<string, VillagerData>;

int clampInt(int x, int lo, int hi) {
    if (x < lo) return lo;
    if (x > hi) return hi;
    return x;
}

void printAll (const VillagerMap& m) {
    cout << "\nVillager details:\n";
    for (const auto& [name, data] : m) {
        const auto& [friendship, species, catchphrase] = data;
        cout << name << " [" << friendship << ", " << species << ", "
             << "\"" << catchphrase << "\"]\n";
    }
    if (m.empty()) cout << "(no villagers)\n";
    cout << endl;
}

bool searchVillager (const VillagerMap& m, const string& key){
    auto it = m.find(key);
    if (it == m.end()) { cout << key << " not found.\n"; return false; }
    const auto& [f, s, c] = it->second;
    cout << "Found " << key << " [" << f << ", " << s << ", " << "\"" << c << "\"]\n";
    return true;
}

void increaseFriendship (VillagerMap& m, const string& key){
    auto it = m.find(key);
    if (it == m.end()) { cout << key << " not found.\n"; return; }
    auto& [f, s, c] = it->second;
    f = clampInt(f + 1, 0, 10);
    cout << key << " friendship increased to " << f << ".\n";
}

void decreaseFriendship (VillagerMap& m, const string& key){
    auto it = m.find(key);
    if (it == m.end()) { cout << key << " not found.\n"; return; }
    auto& [f, s, c] = it->second;
    f = clampInt(f - 1, 0, 10);
    cout << key << " friendship decreased to " << f << ".\n";
}

void addVillager (VillagerMap& m){
    string name, species, catchphrase;
    int friendship;

    cout << "\nVillager name: ";
    getline(cin, name);
    if (name.empty()) { cout << "Name cannot be empty.\n"; return; }

    cout << "Friendship level (0-10): ";
    if (!(cin >> friendship)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid number.\n"; 
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    friendship = clampInt(friendship, 0, 10);

    cout << "Species: ";
    getline(cin, species);

    cout << "Catchphrase: ";
    getline(cin, catchphrase);

    m[name] = VillagerData{friendship, species, catchphrase};
    cout << name << " added.\n";
}

void deleteVillager(VillagerMap& m, const string& key) {
    size_t erased = m.erase(key);
    if (erased) cout << key << " deleted.\n";
    else        cout << key << " not found.\n";
}

int main() {
    VillagerMap villagers;

    villagers["Audie"] = VillagerData{6, "Wolf", "Yippee!!"};
    villagers["Raymond"] = make_tuple(8, "Cat", "Awesome!!");
    villagers.insert({"Marshal", VillagerData{7, "Squirrel", "Noooo!!"}});

    while (true){
        cout << "==============================\n";
        cout << "1. Add Villager\n";
        cout << "2. Delete Villager\n";
        cout << "3. Increase Friendship\n";
        cout << "4. Decrease Friendship\n";
        cout << "5. Search for Villager\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";

        int choice = 0;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input.\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 6) { cout << "Goodbye!\n"; break; }

        string name;
        switch (choice) {
            case 1:
                addVillager(villagers);
                printAll(villagers);
                break;
            case 2:
                cout << "\nVillager name to delete: ";
                getline(cin, name);
                deleteVillager(villagers, name);
                printAll(villagers);
                break;
            case 3:
                cout << "\nVillager name to increase friendship: ";
                getline(cin, name);
                increaseFriendship(villagers, name);
                printAll(villagers);
                break;
            case 4:
                cout << "\nVillager name to decrease friendship: ";
                getline(cin, name);
                decreaseFriendship(villagers, name);
                printAll(villagers);
                break;
            case 5:
                cout << "\nVillager name to search: ";
                getline(cin, name);
                searchVillager(villagers, name);
                break;
            default:
                cout << "Please choose 1-6.\n";
        }
    }
    return 0;
}
