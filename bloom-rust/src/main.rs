mod bloom;

fn main() {
    let mut bloom: bloom::Bloom<u32> = bloom::Bloom::new(5000, 7);

    bloom::add(&mut bloom, &1);
    bloom::add(&mut bloom, &2);
    bloom::add(&mut bloom, &3);

    let queries = 1000;
    let mut positives = 0;

    for i in 0..queries {
        positives += if bloom::query(&bloom, &i) { 1 } else { 0 };
    }

    println!("Percentage of positives: {}", ((positives * 100) as f64) / (queries as f64));
}
