extern crate bit_vec;

use std::hash::{Hash, Hasher, SipHasher};
use std::marker::PhantomData;

pub struct Bloom<T: Hash> {
    size: usize,
    hashes: usize,
    bit_array: bit_vec::BitVec,
    phantom: PhantomData<T>,
}

impl<T> Bloom<T> where T: Hash {
    pub fn new(size: usize, hashes: usize) -> Bloom<T> {
        Bloom {
            size: size,
            hashes: hashes,
            bit_array: bit_vec::BitVec::from_elem(size, false),
            phantom: PhantomData,
        }
    }
}

pub fn add<T>(bloom: &mut Bloom<T>, value: &T) where T: Hash {
    let mut x = first_hash(value) % bloom.size;
    let mut y = second_hash(value) % bloom.size;

    bloom.bit_array.set(x, true);

    for i in 1..bloom.hashes {
        x = (x + y) % bloom.size;
        y = (y + i) % bloom.size;

        bloom.bit_array.set(x, true);
    }
}

pub fn query<T>(bloom: &Bloom<T>, value: &T) -> bool
    where T: Hash {
    let mut x = first_hash(value) % bloom.size;
    let mut y = second_hash(value) % bloom.size;

    if !bloom.bit_array.get(x).unwrap() {
        return false;
    }

    for i in 1..bloom.hashes {
        x = (x + y) % bloom.size;
        y = (y + i) % bloom.size;

        if !bloom.bit_array.get(x).unwrap() {
            return false;
        }
    }

    true
}

fn first_hash<T>(value: &T) -> usize where T: Hash {
    let mut sip_hasher = SipHasher::new_with_keys(0, 0);
    value.hash(&mut sip_hasher);
    sip_hasher.finish() as usize
}

fn second_hash<T>(value: &T) -> usize where T: Hash {
    let mut sip_hasher = SipHasher::new_with_keys(1, 1);
    value.hash(&mut sip_hasher);
    sip_hasher.finish() as usize
}
