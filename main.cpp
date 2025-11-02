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

void printAll(const VillagerMap& m) {
    cout << "Villager details:\n";
    for (const auto& [name, data] : m) {
        const auto& [friendship, species, catchphrase] = data;
        cout << name << " [" << friendship << ", " << species << ", "
             << "\"" << catchphrase << "\"]\n";
    }
    if (m.empty()) cout << "(no villagers)\n";
    cout << endl;
}

bool searchVillager(const VillagerMap& m, const string& key){
    auto it = m.find(key);
    if (it == m.end()) { cout << key << " not found.\n"; return false; }
    const auto& [f, s, c] = it->second;
    cout << "Found " << key << " [" << f << ", " << s << ", " << "\"" << c << "\"]\n";
    return true;
}

void increaseFriendship(VillagerMap& m, const string& key){
    auto it = m.find(key);
    if (it == m.end()) { cout << key << " not found.\n"; return; }
    auto& [f, s, c] = it->second;
    f = clampInt(f + 1, 0, 10);
    cout << key << " friendship increased to " << f << ".\n";
}


int main() {
    VillagerMap villagers;

    villagers["Audie"] = VillagerData{6, "Wolf", "Yippee!!"};
    villagers["Raymond"] = make_tuple(8, "Cat", "Awesome!!");
    villagers.insert({"Marshal", VillagerData{7, "Squirrel", "Noooo!!"}});

    if (auto it = villagers.find("Raymond"); it != villagers.end()) {
        auto& [f, s, c] = it->second;
        cout << "Access: Raymond -> friendship=" << f
             << ", species=" << s
             << ", catchphrase=\"" << c << "\"\n\n";
    }

    printAll(villagers);

    return 0;
}