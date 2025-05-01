import csv
import math

# Step 3: Main program logic
def main():
    with open("AL2023stats.csv", 'r') as file:
        reader = csv.DictReader(file)
        teams = [row for row in reader]
    

    print("Welcome! Select a team from the list.")
    print("\nList of teams:")
    for index, team in enumerate(teams):
        print(f"{index + 1}. {team['Name']}")
    selected_team_index = int(input("Enter the number corresponding to your team: ")) - 1
    selected_team = teams[selected_team_index]

    team_name = selected_team['Name']
    runs_scored = int(selected_team['R'])
    runs_allowed = int(selected_team['RA'])
    games_played = int(selected_team['G'])
    actual_wins_2023 = int(selected_team['W'])

    winning_percentage = runs_scored**2 / (runs_scored**2 + runs_allowed**2)
    expected_wins_2023 = round(winning_percentage * games_played)

    print("\n2023 Season Results:")
    print(f"Team: {team_name}")
    print(f"Runs Scored (R): {runs_scored}")
    print(f"Runs Allowed (RA): {runs_allowed}")
    print(f"Games Played (G): {games_played}")
    print(f"Actual Wins: {actual_wins_2023}")
    print(f"Expected Wins: {expected_wins_2023}")

    games_played_2024 = int(input(f"\nHow many games have the {team_name} played in 2024? "))
    actual_wins_2024 = int(input(f"How many games have the {team_name} won in 2024? "))

    expected_wins_2024 = round(winning_percentage * games_played_2024)

    difference_in_wins = abs(expected_wins_2024 - actual_wins_2024)

    print("\n2024 Season Comparison:")
    print(f"Team: {team_name}")
    print(f"Games Played: {games_played_2024}")
    print(f"Actual Wins: {actual_wins_2024}")
    print(f"Expected Wins: {expected_wins_2024}")
    print(f"Difference in Wins: {difference_in_wins}")


if __name__ == "__main__":
    main()
