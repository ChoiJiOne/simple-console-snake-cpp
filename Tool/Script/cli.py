import click

from cmake_helper import CMakeHelper
from config import SolutionConfig, BuildConfig, PackageConfig

@click.group()
def cli():
    pass

@cli.command()
@click.option("--solution-path", required=True)
@click.option("--log-file-path", required=True)
def generate(**kwargs):
    logger = None
    try:
        cmake_helper = CMakeHelper(SolutionConfig, **kwargs)
        logger = cmake_helper.get_logger()
        cmake_helper.run_generate()
    except Exception as e:
        if logger:
            logger.error(f"Generate Failed: {e}")
        else:
            print(f"Generate Failed: {e}")

@cli.command()
@click.option("--solution-path", required=True)
@click.option("--config", type=click.Choice(["Debug", "Release", "RelWithDebInfo", "MinSizeRel"]), required=True)
@click.option("--log-file-path", required=True)
def build(**kwargs):
    logger = None
    try:
        cmake_helper = CMakeHelper(BuildConfig, **kwargs)
        logger = cmake_helper.get_logger()
        cmake_helper.run_build()
    except Exception as e:
        if logger:
            logger.error(f"Build Failed: {e}")
        else:
            print(f"Build Failed: {e}")

@cli.command()
@click.option("--solution-path", required=True)
@click.option("--config", type=click.Choice(["Debug", "Release", "RelWithDebInfo", "MinSizeRel"]), required=True)
@click.option("--log-file-path", required=True)
@click.option("--need-build", type=click.Choice(["true", "false"]), required=True)
def package(**kwargs):
    logger = None
    try:
        cmake_helper = CMakeHelper(PackageConfig, **kwargs)
        logger = cmake_helper.get_logger()
        cmake_helper.run_package()
    except Exception as e:
        if logger:
            logger.error(f"Build Failed: {e}")
        else:
            print(f"Build Failed: {e}")

if __name__ == "__main__":
    cli()