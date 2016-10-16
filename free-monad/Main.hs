{-# LANGUAGE OverloadedStrings #-}
{-# LANGUAGE RankNTypes #-}
{-# LANGUAGE GADTs #-}
{-# LANGUAGE DataKinds #-}
{-# LANGUAGE PolyKinds #-}
{-# LANGUAGE TypeFamilies #-}
{-# LANGUAGE CPP #-}
{-# LANGUAGE BangPatterns #-}
{-# LANGUAGE FlexibleInstances #-}

module Main where

import BankMonad

example' = do
  create (Account "JOhn doe" (fromIntegral 1000))

example = do
  acc <- create (Account "John Doe" (fromIntegral 5))
  balance <- balance acc
  withdraw (fromIntegral 2)

main = return ()
