#!/usr/bin/python3
# run_length_decoder_generator.py
# Consider a sequence of objects x0, x1, x2, .... A "run" is a maximal
# subsequence of identical objects. The "run-length encoding" of the sequence is
# the sequence c1, y1, c2, y2, ... such that ci is the length of the ith run in
# the original sequence and yi is the value of the objects that make up the run.
# For example, the run-length encoding of the sequence 1, 1, 1, 'x', 'x', [] is
# is 3, 1, 2, 'x', 1, []. Implement a generator that takes an iterable that
# produces the run-length encoding of some sequence as input, and generates the
# original sequence as output.


def run_length_decoding(run_length_encoding):
    run_length = None
    for x in run_length_encoding:
        if run_length is None:
            if (type(x) != int) or (x < 1):
                raise ValueError(f'invalid run length: {run_length}')
            run_length = x
            continue

        for _ in range(run_length):
            yield x

        run_length = None


def main():
    tests = (
        ((3, 1, 2, 'x', 1, []), (1, 1, 1, 'x', 'x', [])),
        ((5, 'x'), ('x', 'x', 'x', 'x', 'x')),
    )
    sols = (run_length_decoding, )

    correct_counts = {sol: 0 for sol in sols}
    for test_index, (data, want) in enumerate(tests):
        print(f'Test {test_index + 1}:')
        print(f'data = {data}')
        print(f'want = {want}')

        for sol in sols:
            got = tuple(run_length_decoding(data))
            if got == want:
                print(f'{sol.__name__} passes')
                correct_counts[sol] += 1
            else:
                print(f'{sol.__name__} fails; got = {got}')

        print()

    print('Summary:')
    for sol in sols:
        print(f'{sol.__name__}: {correct_counts[sol]} of {len(tests)} correct')


if __name__ == '__main__':
    main()
