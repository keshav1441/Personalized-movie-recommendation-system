#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <sstream>
#include <vector>
using namespace std;

const int NUM_USERS = 400;
const int NUM_MOVIES = 500;
const std::string OUTPUT_FILE = "rating.csv";

int generateRating()
{
    int r = rand() % 10;
    if (r < 4)
        return 0;
    return rand() % 5 + 1;
}

vector<vector<int>> loadRatings(const string& filename) {
    vector<vector<int>> ratings;
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        vector<int> row;
        stringstream ss(line);
        string value;
        while (getline(ss, value, ',')) {
            row.push_back(stoi(value)); 
        }
        ratings.push_back(row);
    }
    return ratings;
}

double calculateSimilarity(const vector<int>& user1, const vector<int>& user2) {
    double dotProduct = 0.0, normA = 0.0, normB = 0.0;

    for (size_t i = 0; i < user1.size(); ++i) {
        dotProduct += user1[i] * user2[i];
        normA += user1[i] * user1[i];
        normB += user2[i] * user2[i];
    }

    return (normA == 0 || normB == 0) ? 0.0 : dotProduct / (sqrt(normA) * sqrt(normB));
}

double predictRating(int targetUser, int movie, const vector<vector<int>>& ratings) {
    double numerator = 0.0, denominator = 0.0;

    for (size_t otherUser = 0; otherUser < ratings.size(); ++otherUser) {
        if (otherUser == targetUser) continue; 

        double similarity = calculateSimilarity(ratings[targetUser], ratings[otherUser]);
        if (ratings[otherUser][movie] > 0) { 
            numerator += similarity * ratings[otherUser][movie];
            denominator += abs(similarity);
        }
    }
    return (denominator == 0) ? 0.0 : numerator / denominator;
}

struct MovieRecommendation {
    int movieID;
    double predictedRating;
};

vector<MovieRecommendation> recommendMovies(int targetUser, const vector<vector<int>>& ratings, int topN) {
    vector<MovieRecommendation> recommendations;
    for (size_t movie = 0; movie < ratings[targetUser].size(); ++movie) {
        if (ratings[targetUser][movie] == 0) { 
            double predictedRating = predictRating(targetUser, movie, ratings);
            recommendations.push_back({(int)movie, predictedRating});
        }
    }
    sort(recommendations.begin(), recommendations.end(), [](const MovieRecommendation& a, const MovieRecommendation& b) {
        return a.predictedRating > b.predictedRating;
    });
    if ((int)recommendations.size() > topN) {
        recommendations.resize(topN);
    }
    return recommendations;
}

void displayRecommendations(const vector<MovieRecommendation>& recommendations) {
    cout << "Top Recommended Movies:\n";
    for (const auto& rec : recommendations) {
        cout << "Movie " << rec.movieID + 1 << " with predicted rating: " << rec.predictedRating << endl;
    }
}



int main()
{

    vector<vector<int>> ratings = loadRatings("rating.csv");

    int targetUser = 0; 
    int topN = 5;      

    vector<MovieRecommendation> recommendations = recommendMovies(targetUser, ratings, topN);

    displayRecommendations(recommendations);
    

}