#include <benchmark/benchmark.h>
#include <rpnx/serial_traits.hpp>
#include <json.hpp>

static auto get_bm_serial1()
{

    std::string input = "Hello world, serial test!";
    std::vector<char> input2(input.begin(), input.end());
    std::vector<std::vector<char>> input3{ input2, {}, input2 };
    return input3;
}

static void bm_serialize_obj1_to_vector(benchmark::State& state)
{

    auto object_to_serialize = get_bm_serial1();

    for (auto _ : state)
    {
        std::vector<std::uint8_t> output;

        rpnx::quick_functor_serialize(object_to_serialize, [&output](std::size_t n)
            {
                std::size_t size_old = output.size();
                output.resize(size_old + n);
                return output.begin() + size_old;
            });
        benchmark::DoNotOptimize(output.data());
    }
}
BENCHMARK(bm_serialize_obj1_to_vector);

static void bm_serialize_obj1_to_vector_it(benchmark::State& state) 

{

    auto object_to_serialize = get_bm_serial1();

    for (auto _ : state)
    {
        std::vector<std::uint8_t> output;

        rpnx::quick_iterator_serialize(object_to_serialize, std::back_inserter(output));
        benchmark::DoNotOptimize(output.data());
    }

}
BENCHMARK(bm_serialize_obj1_to_vector_it);

static void bm_serialize_obj1_to_vector_it_preallocate(benchmark::State& state)
{
    auto object_to_serialize = get_bm_serial1();

    for (auto _ : state)
    {
        std::vector<std::uint8_t> output;
        output.resize(rpnx::get_serial_size(object_to_serialize));

        rpnx::quick_iterator_serialize(object_to_serialize, output.begin());
        benchmark::DoNotOptimize(output.data());
    }

}
BENCHMARK(bm_serialize_obj1_to_vector_it_preallocate);


static void bm_serialize_obj1_to_json_string(benchmark::State& state)
{
    auto object_to_serialize = get_bm_serial1();

    for (auto _ : state)
    {
        std::string output;
        nlohmann::json js(object_to_serialize);
        output = js.dump();
        benchmark::DoNotOptimize(output.data());
    }

}
BENCHMARK(bm_serialize_obj1_to_json_string);


BENCHMARK_MAIN();