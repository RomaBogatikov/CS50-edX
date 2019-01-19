from nltk.tokenize import sent_tokenize


def lines(a, b):
    """Return lines in both a and b"""
    # split strings a and b into lines
    a_split = a.splitlines()
    b_split = b.splitlines()
    # create a set of lines that are in both a and b
    common = {line for line in a_split if line in b_split}
    # return a list of these lines
    return list(common)


def sentences(a, b):
    """Return sentences in both a and b"""
    # tokenize each string a and b into list of tokens
    a_tokenized = sent_tokenize(a)
    b_tokenized = sent_tokenize(b)
    # a set of unique sentences that are bresent in both a and b
    common = {sentence for sentence in a_tokenized if sentence in b_tokenized}
    # return a list of these tokens
    return list(common)


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""
    # split each string a and b into substrings of length n
    a_substrings = [a[i:i+n] for i in range(len(a) - n + 1)]
    b_substrings = [b[i:i+n] for i in range(len(b) - n + 1)]
    # a set of substrings of length n that are present in both a and b
    common = {substring for substring in a_substrings if substring in b_substrings}
    # return a list of these substrings
    return list(common)
