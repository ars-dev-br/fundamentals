{-# LANGUAGE OverloadedStrings #-}
{-# LANGUAGE RankNTypes #-}
{-# LANGUAGE GADTs #-}
{-# LANGUAGE DataKinds #-}
{-# LANGUAGE PolyKinds #-}
{-# LANGUAGE TypeFamilies #-}
{-# LANGUAGE CPP #-}
{-# LANGUAGE BangPatterns #-}
{-# LANGUAGE FlexibleInstances #-}

module BankMonad ( Owner
                 , Amount
                 , Account(Account)

                 , Banking(..)
                 , BankingF(..)
                 ) where

type Owner = String
type Amount = Rational

data Account = Account Owner Amount
             deriving (Show)

-- | All possible operations.  It should be possible to create an
-- account, make deposits into it, withdraw money from it, and get its
-- current balance.
class Banking f where
  create :: f Account
  deposit :: Amount -> f Amount
  withdraw :: Amount -> f Amount
  balance :: Account -> f Amount

-- | Data structure representing these operations.  This will create
-- an AST from the operations, but will not execute any of it.
data BankingF a = Create (Account -> a)
                | Deposit Amount (Amount -> a)
                | Withdraw Amount (Amount -> a)
                | Balance Account (Amount -> a)

instance Banking BankingF where
  create = Create id
  deposit a = Deposit a id
  withdraw a = Withdraw a id
  balance a = Balance a id
