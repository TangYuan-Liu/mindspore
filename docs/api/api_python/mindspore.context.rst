﻿mindspore.context
===================

MindSpore上下文，用于配置当前执行环境，包括执行模式、执行后端和其他特性开关。

.. py:function:: mindspore.context.set_context(**kwargs)

    设置运行环境的上下文。

    在运行程序之前，应配置上下文。如果没有配置，默认情况下将根据设备目标进行自动设置。

    .. note::
        设置属性时，必须输入属性名称。初始化网络后不建议更改模式，因为某些操作在图模式和PyNative模式下是不同的。默认值：GRAPH_MODE。

    某些配置适用于特定的设备，有关详细信息，请参见下表：

    +-------------------------+------------------------------+----------------------------+
    | 功能分类                |    配置参数                  |          硬件平台支持      |
    +=========================+==============================+============================+
    | 系统配置                |   device_id                  |   CPU/GPU/Ascend           |
    |                         +------------------------------+----------------------------+
    |                         |   device_target              |   CPU/GPU/Ascend           |
    |                         +------------------------------+----------------------------+
    |                         |  max_device_memory           |  GPU                       |
    |                         +------------------------------+----------------------------+
    |                         |  variable_memory_max_size    |  Ascend                    |
    |                         +------------------------------+----------------------------+
    |                         |  mempool_block_size          |  GPU/Ascend                |
    +-------------------------+------------------------------+----------------------------+
    | 调试配置                |  save_graphs                 |  CPU/GPU/Ascend            |
    |                         +------------------------------+----------------------------+
    |                         |  save_graphs_path            |  CPU/GPU/Ascend            |
    |                         +------------------------------+----------------------------+
    |                         |  enable_dump                 |  Ascend                    |
    |                         +------------------------------+----------------------------+
    |                         |  save_dump_path              |  Ascend                    |
    |                         +------------------------------+----------------------------+
    |                         |  enable_profiling            |  Ascend                    |
    |                         +------------------------------+----------------------------+
    |                         |  profiling_options           |  Ascend                    |
    |                         +------------------------------+----------------------------+
    |                         |  print_file_path             |  Ascend                    |
    |                         +------------------------------+----------------------------+
    |                         |  env_config_path             |  CPU/GPU/Ascend            |
    |                         +------------------------------+----------------------------+
    |                         |  precompile_only             |  CPU/GPU/Ascend            |
    |                         +------------------------------+----------------------------+
    |                         |  reserve_class_name_in_scope |  CPU/GPU/Ascend            |
    |                         +------------------------------+----------------------------+
    |                         |  pynative_synchronize        |  GPU/Ascend                |
    +-------------------------+------------------------------+----------------------------+
    | 执行控制                |   mode                       |   CPU/GPU/Ascend           |
    |                         +------------------------------+----------------------------+
    |                         |  enable_graph_kernel         |  Ascend/GPU                |
    |                         +------------------------------+----------------------------+
    |                         |  graph_kernel_flags          |  Ascend/GPU                |
    |                         +------------------------------+----------------------------+
    |                         |  enable_reduce_precision     |  Ascend                    |
    |                         +------------------------------+----------------------------+
    |                         |  auto_tune_mode              |  Ascend                    |
    |                         +------------------------------+----------------------------+
    |                         |  check_bprop                 |  CPU/GPU/Ascend            |
    |                         +------------------------------+----------------------------+
    |                         |  max_call_depth              |  CPU/GPU/Ascend            |
    |                         +------------------------------+----------------------------+
    |                         |  enable_sparse               |  CPU/GPU/Ascend            |
    |                         +------------------------------+----------------------------+
    |                         |  grad_for_scalar             |  CPU/GPU/Ascend            |
    |                         +------------------------------+----------------------------+
    |                         |  save_compile_cache          |  CPU/GPU/Ascend            |
    |                         +------------------------------+----------------------------+
    |                         |  load_compile_cache          |  CPU/GPU/Ascend            |
    +-------------------------+------------------------------+----------------------------+

    **参数：**

    - **device_id** (int) - 表示目标设备的ID，其值必须在[0, device_num_per_host-1]范围中，且 `device_num_per_host` 的值不应超过4096。默认值：0。
    - **device_target** (str) - 表示待运行的目标设备，支持Ascend、GPU和CPU。如果未设置设备目标，则使用MindSpore包的版本。
    - **max_device_memory** (str) - 设置设备可用的最大内存。目前，仅在GPU上支持。格式为“xxGB”。默认值：1024GB。实际使用的内存大小是设备的可用内存和 `max_device_memory` 值中的最小值。
    - **variable_memory_max_size** (str) - 设置可变内存的最大值。默认值：30GB。设置此参数后，框架使用的最大内存受配置值的限制。
    - **mempool_block_size** (str) - 设置PyNative模式下设备内存池的块大小。格式为“xxGB”。默认值：1GB。最小值是1GB。实际使用的内存池块大小是设备的可用内存和 `mempool_block_size` 值中的最小值。
    - **save_graphs** (bool) - 表示是否保存图形。默认值：False。当 `save_graphs` 属性设为True时， `save_graphs_path` 属性用于设置中间编译图的存储路径。默认情况下，图形保存在当前目录下。
    - **save_graphs_path** (str) - 表示保存图形的路径。默认值："."。如果指定的目录不存在，系统将自动创建该目录。在分布式训练中，图形将被保存到 `save_graphs_path/rank_${rank_id}/` 目录下。 `rank_id` 为集群中当前设备的ID。
    - **enable_dump** (bool) - 此参数已弃用，将在下一版本中删除。
    - **save_dump_path** (str) - 此参数已弃用，将在下一版本中删除。
    - **enable_profiling** (bool) - 此参数已弃用，将在下一版本中删除。请使用mindspore.profiler.Profiler API。
    - **profiling_options** (str) - 此参数已弃用，将在下一版本中删除。请使用mindspore.profiler.Profiler API。
    - **print_file_path** (str) - 表示用于保存打印数据的路径。如果设置了该参数，默认将打印数据保存到文件中。如果不设置 `print_file_path` ，则显示该屏幕。如果保存的文件已经存在，将添加时间戳后缀到文件中。将数据保存到文件中，解决了在产生大量数据时屏幕打印中数据丢失的问题。如果没有设置该参数，则会报错：prompt to set the upper absolute path。
    - **env_config_path** (str) - 通过context.set_context(env_config_path="./mindspore_config.json")来配置DFX的路径。

      配置Running Data Recorder：

      - **enable**：表示在发生故障时是否启用Running Data Recorder去收集和保存训练中的关键数据。设置为True时，将打开Running Data Recorder。设置为False时，将关闭Running Data Recorder。
      - **path**：设置Running Data Recorder保存数据的路径。当前路径必须是一个绝对路径。

      内存重用：

      - **mem_Reuse**：表示内存复用功能是否打开。设置为True时，将打开内存复用功能。设置为False时，将关闭内存复用功能。

    - **precompile_only** (bool) - 表示是否仅预编译网络。默认值：False。设置为True时，仅编译网络，而不执行网络。
    - **reserve_class_name_in_scope** (bool) - 表示是否将网络类名称保存到所属作用域中。默认值：True。每个节点都有一个作用域。子节点的作用域是其父节点。如果 `reserve_class_name_in_scope` 设置为True，则类名将保存在作用域中的关键字“net-”之后。例如：

      Default/net-Net1/net-Net2 (reserve_class_name_in_scope=True)

      Default/net/net (reserve_class_name_in_scope=False)

    - **pynative_synchronize** (bool) - 表示是否在PyNative模式下启动设备同步执行。默认值：False。设置为False时，将在设备上异步执行算子。当算子执行出错时，将无法定位特定错误脚本代码的位置。当设置为True时，将在设备上同步执行算子。这将降低程序的执行性能。此时，当算子执行出错时，可以根据错误的调用栈来定位错误脚本代码的位置。
    - **mode** (int) - 表示在GRAPH_MODE(0)或PYNATIVE_MODE(1)模式中的运行。默认值：GRAPH_MODE(0)。GRAPH_MODE或PYNATIVE_MODE可以通过 `mode` 属性设置，两种模式都支持所有后端。默认模式为GRAPH_MODE。
    - **enable_graph_kernel** (bool) - 表示是否启用图算融合去优化网络执行性能。默认值：False。如果 `enable_graph_kernel` 设置为True，则可以启用加速。有关图算融合的详细信息，请查看 `使能图算融合 <https://www.mindspore.cn/docs/programming_guide/zh-CN/master/enable_graph_kernel_fusion.html>`_ 。
    - **graph_kernel_flags** (str) - 图算融合的优化选项，当与enable_graph_kernel冲突时，它的优先级更高。其仅适用于有经验的用户。例如，context.set_context(graph_kernel_flags="--opt_level=2 --dump_as_text")。一些常用选项：

      - **opt_level**：设置优化级别。默认值：2。当opt_level的值大于0时，启动图算融合。可选值包括：

        - 0：关闭图算融合。
        - 1：启动算子的基本融合。
        - 2：包括级别1的所有优化，并打开更多的优化，如CSE优化算法、算术简化等。
        - 3：包括级别2的所有优化，并打开更多的优化，如SitchingFusion、ParallelFusion等。在某些场景下，该级别的优化激进且不稳定。使用此级别时要小心。

      - **dump_as_text**：将详细信息转储为文本文件。默认值：False。

        有关更多选项，可以参考实现代码。

    - **enable_reduce_precision** (bool) - 表示是否开启降低精度计算。默认值：True。设置为True时，不支持用户指定的精度，且精度将自动更改。设置为False时，如果未指定用例的精度，则会报错并退出。
    - **auto_tune_mode** (str) - 表示算子构建时的自动调整模式，以获得最佳的切分性能。默认值：NO_TUNE。其值必须在['RL', 'GA', 'RL,GA']范围中。

      - RL：强化学习调优。
      - GA：遗传算法调优。
      - RL，GA：当RL和GA优化同时打开时，工具会根据网络模型中的不同算子类型自动选择RL或GA。RL和GA的顺序没有区别。（自动选择）。


      有关启用算子调优工具设置的更多信息，请查看 `使能算子调优工具 <https://www.mindspore.cn/docs/programming_guide/zh-CN/master/enable_auto_tune.html>`_。

    - **check_bprop** (bool) - 表示是否检查反向传播节点，以确保反向传播节点输出的形状(shape)和数据类型与输入参数相同。默认值：False。
    - **max_call_depth** (int) - 指定函数调用的最大深度。其值必须为正整数。默认值：1000。当嵌套Cell太深或子图数量太多时，需要设置 `max_call_depth` 参数。如果 `max_call_depth` 的值比以前的大，则应把系统最大堆栈深度设得更大，否则可能会因为系统堆栈溢出而引发 `core dumped` 异常。
    - **enable_sparse** (bool) - 表示是否启用稀疏特征。默认值：False。有关稀疏特征和稀疏张量的详细信息，请查看 `稀疏张量 <https://www.mindspore.cn/docs/programming_guide/zh-CN/master/tensor.html#sparse-tensor>`_。
    - **grad_for_scalar** (bool)：  表示是否获取标量梯度。默认值：False。当 `grad_for_scalar` 设置为True时，则衍生函数的标量输入。默认值为False。由于后端目前不支持伸缩操作，所以该接口只支持在前端可推演的简单操作。
    - **enable_compile_cache** (bool) - 表示是否加载或者保存前端编译的图。当 `enable_compile_cache` 被设置为True时，在第一次执行的过程中，一个硬件无关的编译缓存会被生成并且导出为一个MINDIR文件。当该网络被再次执行时，如果 `enable_compile_cache` 仍然为True并且网络脚本没有被更改，那么这个编译缓存会被加载。注意目前只支持有限的Python脚本更改的自动检测，这意味着可能有正确性风险。默认值：False。这是一个实验原型，可能会被更改或者删除。
    - **compile_cache_path** (str) - 保存前端图编译缓存的路径。默认值："."。如果目录不存在，系统会自动创建这个目录。缓存会被保存到如下目录：`compile_cache_path/rank_${rank_id}/` 。 `rank_id` 是集群上当前设备的ID。

    **异常：**

    **ValueError**：输入key不是上下文中的属性。

    **样例：**

    >>> context.set_context(mode=context.PYNATIVE_MODE)
    >>> context.set_context(precompile_only=True)
    >>> context.set_context(device_target="Ascend")
    >>> context.set_context(device_id=0)
    >>> context.set_context(save_graphs=True, save_graphs_path="./model.ms")
    >>> context.set_context(enable_reduce_precision=True)
    >>> context.set_context(enable_dump=True, save_dump_path=".")
    >>> context.set_context(enable_graph_kernel=True)
    >>> context.set_context(graph_kernel_flags="--opt_level=2 --dump_as_text")
    >>> context.set_context(reserve_class_name_in_scope=True)
    >>> context.set_context(variable_memory_max_size="6GB")
    >>> context.set_context(enable_profiling=True,
    ...                     profiling_options='{"output":"/home/data/output","training_trace":"on"}')
    >>> context.set_context(check_bprop=True)
    >>> context.set_context(max_device_memory="3.5GB")
    >>> context.set_context(mempool_block_size="1GB")
    >>> context.set_context(print_file_path="print.pb")
    >>> context.set_context(enable_sparse=True)
    >>> context.set_context(max_call_depth=80)
    >>> context.set_context(env_config_path="./env_config.json")
    >>> context.set_context(auto_tune_mode="GA,RL")
    >>> context.set_context(grad_for_scalar=True)
    >>> context.set_context(save_compile_cache=True)
    >>> context.set_context(load_compile_cache=True)
    >>> context.set_context(pynative_synchronize=True)

.. py:function:: mindspore.context.get_context(attr_key)

    根据输入key获取上下文中的属性值。如果某些属性没有设置，则会自动获取这些属性的默认值。

    **参数：**

    - **attr_key** (str) - 属性的key。

    **返回：**

    Object，表示给定属性key的值。

    **异常：**

    **ValueError**：输入key不是上下文中的属性。

    **样例：**

    >>> context.get_context("device_target")
    >>> context.get_context("device_id")

.. py:function:: mindspore.context.set_auto_parallel_context(**kwargs)

    配置自动并行，仅在Ascend和GPU上有效。

    应在mindspore.communication.init之前配置自动并行。

    .. note::
        配置时，必须输入配置的名称。如果某个程序具有不同并行模式下的任务，需要提前调用reset_auto_parallel_context()为下一个任务设置新的并行模式。若要设置或更改并行模式，必须在创建任何Initializer之前调用接口，否则，在编译网络时，可能会出现RuntimeError。

    某些配置适用于特定的并行模式，有关详细信息，请参见下表：

    =========================  =========================
             Common                  AUTO_PARALLEL
    =========================  =========================
    device_num                 gradient_fp32_sync
    global_rank                loss_repeated_mean
    gradients_mean             auto_parallel_search_mode
    parallel_mode              strategy_ckpt_load_file
    all_reduce_fusion_config   strategy_ckpt_save_file
    enable_parallel_optimizer  dataset_strategy
    \                          pipeline_stages
    \                          grad_accumulation_step
    =========================  =========================

    **参数：**

    - **device_num** (int) - 表示可用设备的编号，必须在[1,4096]范围中。默认值：1。
    - **global_rank** (int) - 表示全局RANK的ID，必须在[0,4095]范围中。默认值：0。
    - **gradients_mean** (bool) - 表示是否在梯度的 AllReduce后执行平均算子。stand_alone不支持gradients_mean。默认值：False。
    - **gradient_fp32_sync** (bool)：在FP32中运行梯度的 AllReduce。stand_alone、data_parallel和hybrid_parallel不支持gradient_fp32_sync。默认值：True。
    - **parallel_mode** (str) - 有五种并行模式，分别是stand_alone、data_parallel、hybrid_parallel、semi_auto_parallel和auto_parallel。默认值：stand_alone。

      - stand_alone：单卡模式。
      - data_parallel：数据并行模式。
      - hybrid_parallel：手动实现数据并行和模型并行。
      - semi_auto_parallel：半自动并行模式。
      - auto_parallel：自动并行模式。

    - **auto_parallel_search_mode** (str) - 表示有两种策略搜索模式，分别是recursive_programming和dynamic_programming。默认值：dynamic_programming。

      - recursive_programming：表示双递归搜索模式。
      - dynamic_programming：表示动态规划搜索模式。

    - **parameter_broadcast** (bool) - 表示在训练前是否广播参数。在训练之前，为了使所有设备的网络初始化参数值相同，请将设备0上的参数广播到其他设备。不同并行模式下的参数广播不同。在data_parallel模式下，除layerwise_parallel属性为True的参数外，所有参数都会被广播。在hybrid_parallel、semi_auto_parallel和auto_parallel模式下，分段参数不参与广播。默认值：False。
    - **strategy_ckpt_load_file** (str) - 表示用于加载并行策略checkpoint的路径。默认值：''。
    - **strategy_ckpt_save_file** (str) - 表示用于保存并行策略checkpoint的路径。默认值：''。
    - **full_batch** (bool) - 如果在auto_parallel模式下加载整个batch数据集，则此参数应设置为True。默认值：False。目前不建议使用该接口，建议使用dataset_strategy来替换它。
    - **dataset_strategy** (Union[str, tuple]) - 表示数据集分片策略。默认值：data_parallel。dataset_strategy="data_parallel"等于full_batch=False，dataset_strategy="full_batch"等于full_batch=True。对于通过模型并列策略加载到网络的数据集，如ds_stra ((1, 8)、(1, 8))，需要使用set_auto_parallel_context(dataset_strategy=ds_stra)。
    - **enable_parallel_optimizer** (bool) - 这是一个开发中的特性，它可以为数据并行训练对权重更新计算进行分片，以节省时间和内存。目前，自动和半自动并行模式支持Ascend和GPU中的所有优化器。数据并行模式仅支持Ascend中的 `Lamb` 和 `AdamWeightDecay` 。默认值：False。
    - **all_reduce_fusion_config** (list) - 通过参数索引设置 AllReduce 融合策略。仅支持ReduceOp.SUM和HCCL_WORLD_GROUP/NCCL_WORLD_GROUP。没有默认值。如果不设置，则关闭算子融合。
    - **pipeline_stages** (int) - 设置pipeline并行的阶段信息。这表明了设备如何单独分布在pipeline上。所有的设备将被划分为pipeline_stags个阶段。目前，这只能在启动semi_auto_parallel模式的情况下使用。默认值：1。
    - **grad_accumulation_step** (int) - 在自动和半自动并行模式下设置梯度的累积step。其值应为正整数。默认值：1。

    **异常：**

    **ValueError**：输入key不是自动并行上下文中的属性。

    **样例：**

    >>> context.set_auto_parallel_context(device_num=8)
    >>> context.set_auto_parallel_context(global_rank=0)
    >>> context.set_auto_parallel_context(gradients_mean=True)
    >>> context.set_auto_parallel_context(gradient_fp32_sync=False)
    >>> context.set_auto_parallel_context(parallel_mode="auto_parallel")
    >>> context.set_auto_parallel_context(auto_parallel_search_mode="dynamic_programming")
    >>> context.set_auto_parallel_context(parameter_broadcast=False)
    >>> context.set_auto_parallel_context(strategy_ckpt_load_file="./strategy_stage1.ckpt")
    >>> context.set_auto_parallel_context(strategy_ckpt_save_file="./strategy_stage1.ckpt")
    >>> context.set_auto_parallel_context(dataset_strategy=((1, 8), (1, 8)))
    >>> context.set_auto_parallel_context(enable_parallel_optimizer=False)
    >>> context.set_auto_parallel_context(all_reduce_fusion_config=[8, 160])
    >>> context.set_auto_parallel_context(pipeline_stages=2)

.. py:function:: mindspore.context.get_auto_parallel_context(attr_key)

    根据key获取自动并行的配置。

    **参数：**

    - **attr_key** (str) - 配置的key。

    **返回：**

    根据key返回配置的值。

    **异常：**

    **ValueError**：输入key不在自动并行的配置列表中。

    **样例：**

    >>> from mindspore import context
    >>> parallel_mode = context.get_auto_parallel_context("parallel_mode")
    >>> dataset_strategy = context.get_auto_parallel_context("dataset_strategy")

.. py:function:: mindspore.context.reset_auto_parallel_context()

    重置自动并行的配置为默认值。

    - device_num：1。
    - global_rank：0。
    - gradients_mean：False。
    - gradient_fp32_sync：True。
    - parallel_mode：'stand_alone'。
    - auto_parallel_search_mode：'dynamic_programming'。
    - parameter_broadcast：False。
    - strategy_ckpt_load_file：''。
    - strategy_ckpt_save_file：''。
    - full_batch：False。
    - enable_parallel_optimizer：False。
    - pipeline_stages：1。

.. py:class:: mindspore.context.ParallelMode

    并行模式。

    有五种并行模式，分别是STAND_ALONE、DATA_PARALLEL、HYBRID_PARALLEL、SEMI_AUTO_PARALLEL和AUTO_PARALLEL。默认值：STAND_ALONE。

    - STAND_ALONE：单卡模式。
    - DATA_PARALLEL：数据并行模式。
    - HYBRID_PARALLEL：手动实现数据并行和模型并行。
    - SEMI_AUTO_PARALLEL：半自动并行模式。
    - AUTO_PARALLEL：自动并行模式。

    MODE_LIST：表示所有支持的并行模式的列表。

.. py:function:: mindspore.context.set_ps_context(**kwargs)

    设置参数服务器训练模式的上下文。

    .. note::
        需要给参数服务器训练模式设置其他的环境变量。些环境变量如下所示：

        - MS_SERVER_NUM：表示参数服务器数量。
        - MS_WORKER_NUM：表示工作进程数量。
        - MS_SCHED_HOST：表示调度器IP地址。
        - MS_SCHED_PORT：表示调度器开启的监听端口。
        - MS_ROLE：表示进程角色，角色列表如下：

          - MS_SCHED：表示调度器。
          - MS_WORKER：表示工作进程。
          - MS_PSERVER/MS_SERVER：表示参数服务器。

    **参数：**

    - **enable_ps** (bool) - 表示是否启用参数服务器训练模式。只有在enable_ps设置为True后，环境变量才会生效。默认值：False。
    - **config_file_path** (string) - 配置文件路径，用于容灾恢复等, 目前参数服务器训练模式仅支持Server容灾。默认值：''。
    - **scheduler_manage_port** (int) - 调度器HTTP端口，对外开放用于接收和处理用户扩容/缩容等请求。默认值：11202。
    - **enable_ssl** (bool) - 设置是否打开SSL认证。默认值：True。
    - **client_password** (str) - 用于解密客户端证书密钥的密码。默认值：''。
    - **server_password** (str) - 用于解密服务端证书密钥的密码。默认值：''。


    **异常：**

    **ValueError**：输入key不是参数服务器训练模式上下文中的属性。

    **样例：**

    >>> context.set_ps_context(enable_ps=True, enable_ssl=True, client_password='123456', server_password='123456')

.. py:function:: mindspore.context.get_ps_context(attr_key)

    根据key获取参数服务器训练模式上下文中的属性值。

    **参数：**

    - **attr_key** (str) - 属性的key。

      - enable_ps (bool)：表示是否启用参数服务器训练模式。默认值：False。
      - config_file_path (string)：配置文件路径，用于容灾恢复等。默认值：''。
      - scheduler_manage_port (int)：调度器HTTP端口，对外开放用于接收和处理用户扩容/缩容等请求。默认值：11202。
      - enable_ssl (bool)：设置是否打开SSL认证。默认值：False。
      - client_password (str)：用于解密客户端证书密钥的密码。默认值：''。
      - server_password (str)：用于解密服务端证书密钥的密码。默认值：''。

    **返回：**

    根据key返回属性值。

    **异常：**

    **ValueError** - 输入key不是参数服务器训练模式上下文中的属性。

    **样例：**

    >>> context.get_ps_context(enable_ps)

.. py:function:: mindspore.context.reset_ps_context()

    将参数服务器训练模式上下文中的属性重置为默认值。各字段的含义及其默认值见'set_ps_context'接口。

    **样例：**

    >>> context.reset_ps_context()
