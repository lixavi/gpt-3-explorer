class Translation:
    def __init__(self, gpt3_instance):
        self.gpt3_instance = gpt3_instance
    
    def translate_text(self, text, source_lang, target_lang):
        """
        Translate text from a source language to a target language using OpenAI's GPT-3 model.
        
        Args:
            text (str): The text to translate.
            source_lang (str): The source language code (e.g., 'en' for English).
            target_lang (str): The target language code (e.g., 'fr' for French).
        
        Returns:
            str: The translated text.
        """
        try:
            # Construct prompt for translation
            prompt = f"Translate from {source_lang} to {target_lang}: {text}"

            # Call OpenAI's completion API
            response = self.gpt3_instance.complete(prompt)

            # Extract translated text from API response
            translated_text = response['choices'][0]['text'].strip()
            return translated_text
        except Exception as e:
            print("Error translating text:", e)
            return None
