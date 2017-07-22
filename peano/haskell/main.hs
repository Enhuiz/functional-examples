data Natural = Zero | Successor Natural

plus :: Natural -> Natural -> Natural
plus a Zero = a
plus a (Successor b) = Successor $ plus a b

-- helpers
int_to_natural :: Int -> Natural
int_to_natural 0 = Zero
int_to_natural n | n > 0 = Successor $ int_to_natural $ n - 1
                 | n < 0 = error $ "A Natural number must be a non-negative Integer."

natural_to_int :: Natural -> Int
natural_to_int Zero = 0
natural_to_int (Successor n) = 1 + natural_to_int n

-- main
main = do
    let five = int_to_natural 5
    let ten = int_to_natural 10
    let sum = plus five ten
    let value = natural_to_int sum
    print value