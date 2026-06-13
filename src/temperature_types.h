
namespace Classifications
{
  // Temperature thresholds for classification
  inline constexpr float cold = 0.0f;
  inline constexpr float cool = 10.0f;
  inline constexpr float mild = 18.0f;
  inline constexpr float warm = 27.0f;

}

enum class TemperatureCategory
{
  Cold,
  Cool,
  Mild,
  Warm,
  Hot,
  Unknown
};
