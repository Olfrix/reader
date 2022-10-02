import urllib.request, sys, argparse, math

def get_words_list():
    word_site = "https://www.mit.edu/~ecprice/wordlist.100000"
    response = urllib.request.urlopen(word_site)
    words = response.read().decode()
    return words.splitlines()

def write_words_to_file(words, size):
    size_of_words_in_bytes = sys.getsizeof(words)
    requested_size_in_bytes = size * 1024 * 1024
    counter = requested_size_in_bytes / size_of_words_in_bytes;
    file = open("random_words.txt", "w+")
    for x in range(math.ceil(counter)):
        file.write(" ".join(map(str, words)) + " ")
    file.close()

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("size",
                        help="Generate file with 100000 unique words at least this size (in MB)",
                        type=int)
    args = parser.parse_args()
    write_words_to_file(get_words_list(), args.size)

if __name__ == "__main__":
    main()
