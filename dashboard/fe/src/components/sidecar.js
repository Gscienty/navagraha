import React from 'react';
import { Menu, Icon } from 'antd';
import { connect } from 'react-redux';
import { Link } from 'react-router-dom';

class Sidecar extends React.PureComponent {

    render() {
        return (
            <div style={{ height: 'calc(100%)' }}>
                <Menu
                    mode="vertical"
                    theme="dark">
                    <Menu.Item><Link to="/"><Icon type="dashboard" />控制台</Link></Menu.Item>
                    <Menu.Item><Link to="/namespace"><Icon type="cloud" />命名空间</Link></Menu.Item>
                    <Menu.Item><Link to="/func"><Icon type="deployment-unit" />函数服务</Link></Menu.Item>
                    <Menu.Item><Link to="/monitor"><Icon type="eye" />监控</Link></Menu.Item>
                    <Menu.Item><Link to="api-gateway"><Icon type="gateway" />API 网关</Link></Menu.Item>
                    <Menu.Item><Link to="project"><Icon type="code" />项目</Link></Menu.Item>
                    <Menu.Item><Link to="config-map"><Icon type="file-text" />配置</Link></Menu.Item>
                    <Menu.Item><Link to="node"><Icon type="cloud-server" />主机资产</Link></Menu.Item>
                </Menu>
            </div>
        );
    }
};

export default connect()(Sidecar);
