# Movie Recommendation System in C++

This project implements a **collaborative filtering-based movie recommendation system**. It predicts movie ratings for users and recommends top-rated movies based on user similarities. The system uses **cosine similarity** to measure user similarity and ranks movies for personalized suggestions.

---

## Features

- **Load Rating**: Reads movie ratings from a CSV file into a 2D vector.
- **Cosine Similarity**: Measures similarity between users based on their ratings.
- **Predict Rating**: Predicts ratings for unrated movies for a target user.
- **Top-N Recommendations**: Provides personalized movie recommendations.
- **Easy Extensibility**: Modular design for adding new features.

---

## File Structure

- `main.cpp`: The main file containing all implementations and the entry point.
- `rating.csv`: Input file with user-movie rating .

---

## Prerequisites

- **C++ Compiler**: GCC, Clang, or another C++ compiler supporting C++11 or higher.
- **set**: A CSV file containing the user-movie rating matrix.

---

## Input File Format

The input file (`rating.csv`) should have the following structure:

- Rows represent users.
- Columns represent movies.
- Cell values represent ratings:
  - `0`: Movie is unrated.
  - `1-5`: Valid rating.

**Example:**

```plaintext
5,4,0,3,1
0,0,4,5,3
3,0,0,2,4
...
```

---

## How It Works

1. **Load Rating**: Reads ratings from a file and stores them in a 2D vector.
2. **Calculate Similarity**: Measures similarity between users using cosine similarity.
3. **Predict Rating**: Predicts ratings for unrated movies based on similar users.
4. **Recommend Movies**: Sorts predicted ratings and recommends the top-N movies.

---

## Running the Program

### 1. Compile the Program

```bash
g++ -o recommender main.cpp
```

### 2. Run the Program

```bash
./recommender
```

### 3. Output

The program outputs:
- Predicted ratings for unrated movies for the target user.
- Top-N movie recommendations.

---

## Example Output

```plaintext
Top Recommended Movies:
Movie 12 with predicted rating: 4.75
Movie 24 with predicted rating: 4.5
Movie 37 with predicted rating: 4.25
Movie 42 with predicted rating: 4.1
Movie 8 with predicted rating: 3.9
```

---

## Functions Overview

### 1. **`loadRating`**

- **Description**: Loads the movie rating  from a CSV file into a 2D vector.
- **Prototype**: `vector<vector<int>> loadRating(const string& filename);`
- **Parameters**:
  - `filename`: The path to the CSV file containing the ratings.
- **Returns**: A 2D vector representing the user-movie rating matrix.

---

### 2. **`calculateSimilarity`**

- **Description**: Calculates the cosine similarity between two users.
- **Prototype**: `double calculateSimilarity(const vector<int>& user1, const vector<int>& user2);`
- **Parameters**:
  - `user1`: A vector representing ratings by the first user.
  - `user2`: A vector representing ratings by the second user.
- **Returns**: A double value representing the similarity score.

---

### 3. **`predictRating`**

- **Description**: Predicts the rating for a specific movie for a target user.
- **Prototype**: `double predictRating(int targetUser, int movie, const vector<vector<int>>& rating);`
- **Parameters**:
  - `targetUser`: Index of the user for whom the prediction is made.
  - `movie`: Index of the movie to predict the rating for.
  - `rating`: The 2D user-movie rating matrix.
- **Returns**: A double value representing the predicted rating.

---

### 4. **`recommendMovies`**

- **Description**: Recommends the top-N movies for a given user based on predicted ratings.
- **Prototype**: `vector<MovieRecommendation> recommendMovies(int targetUser, const vector<vector<int>>& rating, int topN);`
- **Parameters**:
  - `targetUser`: Index of the user to recommend movies for.
  - `rating`: The 2D user-movie rating matrix.
  - `topN`: Number of top recommendations to provide.
- **Returns**: A vector of `MovieRecommendation` objects containing movie IDs and predicted ratings.

---

### 5. **`displayRecommendations`**

- **Description**: Displays the recommended movies in a user-friendly format.
- **Prototype**: `void displayRecommendations(const vector<MovieRecommendation>& recommendations);`
- **Parameters**:
  - `recommendations`: A vector of `MovieRecommendation` objects.

---

## Limitations

- Assumes a dense rating matrix; performance may degrade with sparse sets.
- Cold-start problem: Struggles to recommend for new users or movies.
- Limited scalability: May be slower for very large sets.

