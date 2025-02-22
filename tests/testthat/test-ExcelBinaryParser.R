test_that("read_xlsb() works", {
  
  exp <- structure(
    list(
      Description = c("Item 1", "Item 2", "Item 3", "Item 4", "Item 5", "TOTAL"),
      Date = structure(c(19338, 19447, 19358, 19331, 19357, NA), class = "Date"),
      Pct = c(0.25, 0.125, 0.3, 1e-06, 0.324999, 1)
    ),
    class = "data.frame", row.names = c(NA, -6L)
  )
  got <- read_xlsb(path = system.file("extdata", "TestBook.xlsb", package = "readxlsb"), 
                   range = "PORTFOLIO")
  expect_equal(got, exp)
  
  
  got <- read_xlsb(path = system.file("extdata", "TestBook.xlsb", package = "readxlsb"), 
                   range = "UNICODE_STR", col_names = FALSE)
  expect_equal(dim(got), c(1, 1))
  
})

test_that("read numerics correctly (#8)", {
  exp <- structure(list(a = c(-12811.27, -190565.87)),
                   class = "data.frame", row.names = c(NA, -2L))
  got <- read_xlsb(path = system.file("extdata", "TestBook.xlsb", package = "readxlsb"), 
                   sheet = "negative_doubles", col_names = TRUE)
  expect_equal(got, exp)
})
