from gpt3.completion import Completion
from gpt3.utils import authenticate_api, load_configuration

def main():
    # Load API key from configuration file
    try:
        api_key = load_configuration("config.json")["api_key"]
    except FileNotFoundError:
        print("Configuration file not found. Please make sure to create a 'config.json' file.")
        return
    except KeyError:
        print("API key not found in configuration file. Please make sure to include your API key.")
        return

    # Authenticate with OpenAI API
    gpt3_instance = authenticate_api(api_key)
    if not gpt3_instance:
        print("Failed to authenticate with OpenAI API. Please check your API key.")
        return
        

    # Initialize Completion object
    completion = Completion(gpt3_instance)

    # Example prompt for text completion
    prompt = "Once upon a time"

    try:
        # Call the completion API
        completed_text = completion.complete_text(prompt)
        print("Completed Text:")
        print(completed_text)
    except Exception as e:
        print("Error occurred while completing text:", e)

if __name__ == "__main__":
    main()
